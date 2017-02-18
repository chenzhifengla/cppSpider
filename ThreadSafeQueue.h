//
// Created by yingzi on 2017/2/18.
//

#ifndef CPPSPIDER_THREADSAFEQUEUE_H
#define CPPSPIDER_THREADSAFEQUEUE_H

#endif //CPPSPIDER_THREADSAFEQUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>

// 线程安全队列模板类
template<typename T>
class ThreadSafeQueue {
private:
    mutable mutex mtx;  // 互斥量
    queue <T> data_queue;    // 存储的队列
    condition_variable data_cond;   // 条件变量，用来线程同步

public:
    ThreadSafeQueue() {}

    // 压入元素，压入成功后通知其他等待取元素线程
    void push(T value) {
        lock_guard <mutex> lck(mtx);
        data_queue.push(std::move(value));
        data_cond.notify_one();
    }

    // 取出元素，队列为空时使用条件变量阻塞线程，直到有压入元素的线程的通知
    void waitPop(T &value) {
        unique_lock <mutex> lck(mtx);
        data_cond.wait(lck, [this] { return !data_queue.empty(); });
        value = std::move(data_queue.front());
        data_queue.pop();
    }

    // 尝试取出元素，队列为空时返回false
    bool try_pop(T &value) {
        lock_guard <mutex> lck(mtx);
        if (data_queue.mepty()) {
            return false;
        }
        value = std::move(data_queue.front());
        data_queue.pop();
    }

    // 判断是否为空
    bool empty() const {
        lock_guard <mutex> lck(mtx);
        return data_queue.empty();
    }
};