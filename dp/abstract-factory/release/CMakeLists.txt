cmake_minimum_required(VERSION 3.1)
project(release)
set(CMAKE_CXX_STANDARD 11)
aux_source_directory(. SRC_LIST)
add_executable(release ${SRC_LIST})