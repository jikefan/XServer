cmake_minimum_required(VERSION 3.24)
project(XServer C)

set(CMAKE_C_STANDARD 11)

add_executable(XServer src/core/wrap.h src/core/wrap.c src/core/xserver.c src/core/xserver.h src/core/server.c src/core/server.h src/type/x_string.c src/type/x_string.h src/utils/fpromgram.c src/utils/fpromgram.h)
