//
// Created by jikefan on 2023/1/10.
//

#ifndef XSERVER_X_STRING_H
#define XSERVER_X_STRING_H

#include <string.h>
#include <stdlib.h>

// 字符串初始化默认容量
#define DEFAULT_STRING_CAPACITY 16

/**
 * XServer自定义的字符串类型
 */
typedef struct x_string {
    // 指向堆空间的字符串指针
    char* ch_ptr;
    // 字符个数
    int size;
    // 字符数组容量
    int capacity;

} *string;

/**
 * 返回一个指向x_string结构体空间的指针
 * @return
 */
static string create_xstring();

/**
 * 创建一个空的默认的字符串
 * @return
 */
string new_emstring();


/**
 * 创建一个有初始化参数的字符串
 * @param str
 * @return
 */
string new_string(const char* str);

/**
 * 让后面的字符串追加到前面的字符串
 * @param front_str
 * @param rear_str
 * @return
 */
string string_append(string front_str, string rear_str);

/**
 * 释放string的空间
 */
void string_free(string str);

#endif //XSERVER_X_STRING_H
