//
// Created by jikefan on 2023/1/9.
//

#include "wrap.h"

static void print_code_position() {
    printf("[" SERVER_NAME "]:\n");
    printf("\tFile: %s\n" "\tLine: %d\n", __FILE__, __LINE__);
    printf("\t\\__");
}

void sys_err(const char* msg) {
    print_code_position();
    perror(msg);
    exit(1);
}

void sys_warn(const char* msg) {
    print_code_position();
    perror(msg);
    printf("\n");
}

int Socket(int domain, int type, int protocol) {
    int ret = socket(domain, type, protocol);
    if (ret == -1) {
        sys_err("create socket error");
    }
    return ret;
}

int Bind(int sockfd, const struct sockaddr_in *addr, socklen_t addrlen) {
    int ret = bind(sockfd, (struct sockaddr *) addr, addrlen);
    if (ret == -1) {
        sys_err("bind error");
    }
    return ret;
}

int Accept(int sockfd, struct sockaddr_in *addr, socklen_t *addrlen) {
    int ret = -1;
    while (1) {
        ret = accept(sockfd, (struct sockaddr *) addr, addrlen);
        if (ret < 0) {
            if (errno == EINTR || errno == ECONNABORTED) {  // 重试
                continue;
            } else {
                sys_warn("accept error");
                break;
            }
        } else {
            break;
        }
    }
    return ret;
}

int Listen(int sockfd, int backlog) {
    int ret = listen(sockfd, backlog);
    if (ret == -1) {
        sys_err("listen error");
    }
    return ret;
}

int Read(int fd, void *ptr, size_t len) {
    int count = 0;
    char *vptr = ptr;
    while ((count = read(fd, ptr, len)) != 0) {
        if (count > 0) {
            return count;
        } else {    // count < 0
            // 如果被信号意外中断,则重试
            if (errno == EINTR) {
                count = 0;
                ptr = vptr;
                continue;
            } else {
                return -1;
            }
        }
    }
    // count == 0时也会被返回, 表示读取到文件末尾了
    return count;
}

int Write(int fd, void *ptr, size_t len) {
    int count = 0;
    char *vptr = ptr;
    while ((count = write(fd, ptr, len)) != 0) {
        if (count > 0) {
            return count;
        } else {    // count < 0
            // 如果被信号意外中断, 则重试
            if (errno == EINTR) {
                count = 0;
                ptr = vptr;
                continue;
            } else {
                return -1;
            }
        }
    }

    return count;
}

int ReadLine(int fd, void *ptr, size_t len, int fill_zero) {
    char * vptr = ptr;
    // 创建用户区缓存
    int buf_len = 2048;
    char buf[buf_len];

    // 实际读取的字节数
    int read_count = 0;

    while (1) {
        int count = read(fd, buf, buf_len);
        if (count > 0) {
            int w_c = count;
            // 写入实际空间前, 要做空间是否够用的检查
            if ((read_count + count) > len) {
                w_c = len - read_count;
            }
            for (int i = 0; i < w_c; i++) {
                if (buf[i] != '\n') {
                    *vptr = buf[i];
                    vptr++;
                } else {
                    // 给末尾补0
                    if (fill_zero) {
                         ((char *) ptr)[len - 1] = 0;
                    }
                    return read_count + i;
                }
            }
            read_count += w_c;
            // 当实际提供len小于一次读取的长度,那么就直接返回用户提供的长度存储的字节数据
            if (read_count == len) {
                // 给末尾补0
                if (fill_zero) {
                    ((char *) ptr)[len - 1] = 0;
                }
                return read_count;
            }
        } else if (count < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                return count;
            }
        } else { // count == 0
            return read_count;
        }
    }
}