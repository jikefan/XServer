//
// Created by jikefan on 2023/1/10.
//

#include "x_string.h"

static string create_xstring() {
    return malloc(sizeof(struct x_string));
}

string new_emstring() {
    string str = create_xstring();
    str->ch_ptr = calloc(DEFAULT_STRING_CAPACITY, sizeof(char));
    str->size = 0;
    str->capacity = DEFAULT_STRING_CAPACITY;

    return str;
}

string new_string(const char* init_str) {
    int count = 0;
    string str= create_xstring();

    while (init_str[count++]);
    str->ch_ptr = calloc(count, sizeof(char));
    str->size = count - 1;
    str->capacity = count;

    memcpy(str->ch_ptr, init_str, str->size);
    // 末尾补0
    str->ch_ptr[str->capacity] = 0;

    return str;
}

string string_append(string front_str, string rear_str) {
    // 每个字符串容量是包括结束符的, 所以两个字符串拼到一起后, 需要减去一个结束符
    int new_capacity = front_str->capacity + rear_str->capacity - 1;

    string str = create_xstring();
    str->capacity = new_capacity;
    str->size = front_str->size + rear_str->size;
    str->ch_ptr = calloc(new_capacity, sizeof(char));

    memcpy(str->ch_ptr, front_str->ch_ptr, front_str->size);
    char * p = str->ch_ptr + front_str->size;
    memcpy(p, rear_str->ch_ptr, rear_str->size + 1);
    return str;
}

void string_free(string str) {
    free(str->ch_ptr);
    free(str);
}