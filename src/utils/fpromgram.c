//
// Created by jikefan on 2023/1/10.
//

#include "fpromgram.h"
#include <stdio.h>

void fp_foreach_int(int arr[], int size, void (*fn)(int)) {
    for (int i = 0; i < size; ++i) {
        fn(arr[i]);
    }
}

void fp_map_pint(int arr[], int size, void (*fn)(int *)) {
    for (int i = 0; i < size; ++i) {
        fn(arr + i);
    }
}

void fp_map_int(int *arr, int size, int (*fn)(int)) {
    for (int i = 0; i < size; i++) {
        arr[i] = (char) fn(arr[i]);
    }
}

void fp_map_ch(char *arr, int size, int (*fn)(int)) {
    for (int i = 0; i < size; i++) {
        arr[i] = (char) fn(arr[i]);
    }
}
