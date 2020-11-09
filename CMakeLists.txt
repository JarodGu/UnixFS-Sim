cmake_minimum_required(VERSION 3.7)
project(UnixFileSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(UnixFileSystem driver.cpp inode.h record.h disk.h inode.cpp filesystem.cpp filesystem.h record.cpp disk.cpp)