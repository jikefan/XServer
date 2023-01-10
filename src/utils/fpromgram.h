//
// Created by jikefan on 2023/1/10.
// 提供一些现代化的函数式编程中常见的操作数组的函数
//

#ifndef XSERVER_FPROMGRAM_H
#define XSERVER_FPROMGRAM_H

/**
 * 根据size遍历数组对每一个元素执行回调函数
 * @param arr
 * @param size
 * @param fn
 */
void fp_foreach_int(int arr[], int size, void (*fn)(int));

/**
 * 根据size遍历数组元素,对数组元素执行回调函数修改原来的数组
 * 传给回调函数的是元素的地址
 * @param arr
 * @param size
 * @param fn
 */
void fp_map_pint(int arr[], int size, void (*fn)(int *));

/**
 * 根据size遍历数组元素,对数组元素执行回调函数修改原来的数组
 * 传给回调函数的是元素的值
 * @param arr
 * @param size
 * @param fn
 */
void fp_map_int(int *arr, int size, int (*fn)(int));

void fp_map_ch(char *arr, int size, int (*fn)(int));

#endif //XSERVER_FPROMGRAM_H
