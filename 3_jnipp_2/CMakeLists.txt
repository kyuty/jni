# Copyright 2021, Collabora, Ltd.
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.10.2)
project(jnipp)

set(JAVA_INCLUDE_PATH /opt/homebrew/opt/openjdk@17/include/)
set(JAVA_INCLUDE_PATH2 /opt/homebrew/opt/openjdk@17/include/)
set(JAVA_JVM_LIBRARY /opt/homebrew/opt/openjdk@17/libexec/openjdk.jdk/Contents/Home/lib/server/libjvm.dylib)
set(JAVA_AWT_LIBRARY /opt/homebrew/opt/openjdk@17/libexec/openjdk.jdk/Contents/Home/lib/libawt.dylib)

find_package(JNI REQUIRED)
include(CTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

MESSAGE(STATUS "123123 JNI_INCLUDE_DIRS = ${JNI_INCLUDE_DIRS}.")
MESSAGE(STATUS "123123 CMAKE_DL_LIBS = ${CMAKE_DL_LIBS}.")

add_library(jnipp jnipp.cpp)
target_include_directories(
  jnipp
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
  PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(jnipp PUBLIC ${CMAKE_DL_LIBS})

add_subdirectory(tests)
