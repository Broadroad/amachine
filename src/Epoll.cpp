#include "Epoll.h"
#include <unistd.h>

Epoll::Epoll(uint32_t number) {
    _events = new struct epoll_event [number];
    memset(_events, 0, sizeof(struct epoll_event));
    //epoll_create 创建一个epoll的句柄，number用来告诉内核需要监听的数目一共有多大，当创建好epoll句柄后
    //它就会占用一个fd值，在linux下如果查看/proc/进程id/fd/，能够看到这个fd，
    //所以在使用完epoll后，得调用close（）关闭，否则可能导致fd被耗尽。
    _epfd = epoll_create(number);

    if (-1 == _epfd) {
        fprintf(stderr, "epoll create failed");
    };
}

Epoll::~Epoll() {
    close(_epfd);
    delete[] _events;
}

void Epoll::control(int op, int fd, uint32_t event, bool enable_et = false) {
    _ev.data.fd = fd;
    _ev.events = event;
    if (enable_et) {
        _ev.events |= EPOLLET;
    };
    epoll_ctl(_epfd, op, fd, &_ev);    
}

int Epoll::setnonblocking(int sock) {
    int old_option = fcntl(_epfd, F_GETFL);
    int new_option = old_option | O_NONBLOCK;
    fcntl(_epfd, F_SETFL, new_option);
    return old_option;
}

int Epoll::poll(int maxevents, int timeout) {
    return epoll_wait(_epfd, _events, maxevents, timeout);
}


