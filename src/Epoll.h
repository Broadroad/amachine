#ifndef SERVER_H
#define SERVER_H
#include <sys/epoll.h>
#include <iostream>
#include <fcntl.h>
#include <string.h>
#include "config.h"

class Epoll{
public:
    Epoll(uint32_t number);
    Epoll(const Epoll&) = delete;
    //void start();
    ~Epoll();
private:
    int setnonblocking(int sock);
    void control(int op, int fd, uint32_t event, bool enable_et );
    int poll(int maxevents, int timeout);
    epoll_event* get_events() const;
private:
    int _epfd;
    struct epoll_event *_events;
    struct epoll_event _ev;
};
#endif
