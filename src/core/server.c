//
// Created by jikefan on 2023/1/10.
//

#include "server.h"

void sockaddr_init(struct sockaddr* addr, int domain, const char *ip, const int port) {
    struct sockaddr_in addr_in;
    addr_in.sin_family = domain;
    addr_in.sin_port = htons(port);
    inet_pton(domain, ip, &addr_in.sin_addr.s_addr);

    struct sockaddr_in *vaddr = addr;
    *vaddr = addr_in;
}

void sockaddr_sint(struct sockaddr* addr, const int domain, const int port) {
    struct sockaddr_in addr_in;
    addr_in.sin_family = domain;
    addr_in.sin_port = htons(port);
    addr_in.sin_addr.s_addr = htonl(INADDR_ANY);

    struct sockaddr_in *vaddr = addr;
    *vaddr = addr_in;
}

void xserver_launch(int port) {

}