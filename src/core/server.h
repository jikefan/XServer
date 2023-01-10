//
// Created by jikefan on 2023/1/10.
//

#ifndef XSERVER_SERVER_H
#define XSERVER_SERVER_H
#include "wrap.h"
#include <pthread.h>
#include <ctype.h>
#include "../utils/fpromgram.h"

/**
 * 根据参数初始化sockaddr通用地址结构
 * @param addr 传出参数
 * @param domain ip协议类型, 比如AF_INET, AF_INET6
 * @param ip ip地址字符串
 * @param port 整型端口号
 */
void sockaddr_init(struct sockaddr* addr, const int domain, const char *ip, int port);

/**
 * 根据参数初始化服务器端使用的sockaddr通用地址
 * ip自动获取
 * @param addr
 * @param domain
 * @param port
 */
void sockaddr_sint(struct sockaddr* addr, const int domain, const int port);

/**
 * 服务器启动函数
 * @param port 整型端口号
 */
void xserver_launch(int port);

/**
 * socket连接处理函数
 * @param argv socket文件描述符
 */
void* request_handler(void * argv);

/**
 * 打印连接到服务器的客户端信息
 * @param addr
 */
void print_client_info(struct sockaddr_in* addr);

#endif //XSERVER_SERVER_H
