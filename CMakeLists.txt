cmake_minimum_required(VERSION 3.24)

project(ELFTools C)
set(CMAKE_C_STANDARD 11)
add_executable(ELFTools src/main.c include/elf.h)
