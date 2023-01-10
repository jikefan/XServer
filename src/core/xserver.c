//
// Created by jikefan on 2023/1/9.
//
#include "server.h"

#define VERSION "0.0.1"

#define TEST_STATUS 0

int main(int argc, char *argv[]) {
    if (TEST_STATUS) {

    } else {
        if (argc != 2) {
            server_say_tilte();
            printf("\t服务器启动必须提供监听端口号\n");
            exit(1);
        }
        int port = atoi(argv[1]);
        printf("[ XServer " VERSION "] started\n");
        xserver_launch(port);
    }

    return 0;
}
