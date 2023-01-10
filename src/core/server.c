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

void* request_handler(void* argv) {
    int cfd = *(int *) argv;
    char buf[1024];
    int ch_count = 0;
    while (ch_count = ReadLine(cfd, buf, 1024, 0)) {
        if (ch_count < 1024) {
            buf[ch_count - 1] = 0;
        }
        printf("线程: %d\n客户端说: %s\n", cfd, buf);
        fp_map_ch(buf, ch_count, toupper);
        write(cfd, buf, ch_count);
    }
    server_say_tilte();
    printf("线程: %d结束\n", cfd);
    close(cfd);
}

void print_client_info(struct sockaddr_in* addr) {
    char ip[64];
    int port;
    port = ntohs(addr->sin_port);
    inet_ntop(AF_INET, &(addr->sin_addr.s_addr), ip, 64);

    server_say_tilte();
    printf("\tfrom ip = %s, port = %d\n", ip, port);
}


void xserver_launch(int port) {
    struct sockaddr_in addr;
    int sfd = Socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_sint(&addr, AF_INET, port);
    Bind(sfd, &addr, sizeof(addr));
    Listen(sfd, 128);

    struct sockaddr_in clit_addr;
    size_t clit_addr_len = sizeof(clit_addr);

    // 客户端连接个数
    int clit_counts = 0;


    while (1) {
        server_say_tilte();
        printf("waiting...\n");
        int cfd = Accept(sfd, &clit_addr, &clit_addr_len);
        print_client_info(&clit_addr);

        pthread_t tid;
        // 开启线程去处理
        int ret_t = pthread_create(&tid, NULL, request_handler, (void *) &cfd);
        if (ret_t == 0) {
            // 分离线程, 防止出现僵尸线程
            pthread_detach(tid);
        } else {
            errno = ret_t;
            perror("创建线程失败!");
        }
    }
}