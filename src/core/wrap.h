//
// Created by jikefan on 2023/1/9.
//

#ifndef XSERVER_WRAP_H
#define XSERVER_WRAP_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "xserver.h"
#include <sys/socket.h>
#include <arpa/inet.h>

/**
 * 打印服务器特有输出标题
 */
void server_say_tilte();

/**
 * 打印错误信息并退出
 * @param msg 错误信息
 */
void sys_err(const char* msg);

/**
 * 创建一个socket
 * @param domain
 * @param type
 * @param protocol
 * @return 成功返回文件描述符, 失败返回-1, errno
 */
int Socket(int domain, int type, int protocol);

int Bind(int sockfd, const struct sockaddr_in *addr, socklen_t addrlen);

int Accept(int sockfd, struct sockaddr_in *addr, socklen_t *addrlen);

int Listen(int sockfd, int backlog);

/**
 * 根据提供的缓存空间ptr从文件中读取len个字节的数据,
 * 读取过程遇到系统中断EINTR则重试.
 * @param fd   文件描述符
 * @param ptr  缓存空间
 * @param len  缓存大小
 * @return  实际读取到的字节个数
 */
int Read(int fd, void *ptr, size_t len);

int Write(int fd, void *ptr, size_t len);

/**
 * 从文件读取到'\n'终止, 需要缓存有足够大的空间
 * @param fd
 * @param ptr
 * @param len
 * @param fill_zero 0则结果末尾不补0, 1则末尾补0
 * @return
 */
int ReadLine(int fd, void *ptr, size_t len, int fill_zero);

#endif //XSERVER_WRAP_H
