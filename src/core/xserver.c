//
// Created by jikefan on 2023/1/9.
//
#include <stdio.h>
#include "wrap.h"
#include "../type/x_string.h"


int main() {
    string s1 = new_string("hello");
    string s2 = new_string(" world!");
    string s3 = string_append(s1, s2);

    printf("%s\n", s1->ch_ptr);
    printf("%s\n", s2->ch_ptr);
    printf("%s\n", s3->ch_ptr);
    printf("success\n");

    return 0;
}
