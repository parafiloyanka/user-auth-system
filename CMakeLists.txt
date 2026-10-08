cmake_minimum_required(VERSION 3.30)
project(LR5_2_Alieksieieva)

set(CMAKE_CXX_STANDARD 20)

add_executable(LR5_2_Alieksieieva main.cpp
        log.h
        log.cpp
        user.h
        user.cpp
        encrypt.h
        encrypt.cpp
        utils.h
        utils.cpp)
