//
// Created by yingzi on 2016/11/25.
//

#include "Url.h"
#include <regex>

Url::Url(){
    initUrl();
}

// 根据url拆分成Url类对象
Url::Url(string url) {

    initUrl();
    this->url = url;

    string url_pattern("^(https*://)?([^\\s:/]+)(:([0-9]+))?(/[^\\s]*)");
    regex r(url_pattern);

    smatch results;
    if (regex_match(url, results, r)) {
        if (results[1] != "") {
            protocol = results[1];
        }
        if (results[2] != "") {
            host = results[2];
        }
        // results[3]为带:的port号
        if (results[4] != "") {
            port = stoi(results[4]);
        }
        if (results[5] != "") {
            path = results[5];
        }
    }

    //cout << "Init url success!\tprotocol='" << protocol << "'\thost='" << host << "'\tport='" << port << "'\tpath='" << path << "'" << endl;
}

string Url::getUrl() {
    return url;
}

string Url::getFormatUrl() {
    string url = protocol + host;
    if (port != 80) {
        url += to_string(port);
    }
    return url + path;
}

string Url::getProtocol() {
    return protocol;
}

string Url::getHost(){
    return host;
}

int Url::getPort() {
    return port;
}

string Url::getPath(){
    return path;
}

void Url::initUrl() {
    url = "http://yingzinanfei.com/";
    protocol = "http://";
    host = "www.yingzinanfei.com";
    port = 80;
    path = "/";
}
