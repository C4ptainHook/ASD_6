cmake_minimum_required(VERSION 3.23)
project(ASD_lab6_Hash)

set(CMAKE_CXX_STANDARD 20)

add_executable(ASD_lab6_Hash main.cpp DList.h Murmurhash.h Murmurhash.cpp Hashtable.h Generator.h)
