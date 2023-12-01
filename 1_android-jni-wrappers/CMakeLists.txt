# Copyright 2020, Collabora, Ltd.
# SPDX-License-Identifier: BSL-1.0
cmake_minimum_required(VERSION 3.4.1)

# Needed for NDK features
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(JNIPP_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/vendor/jnipp)

# Don't glob things in your own code, manually list them!
file(GLOB WRAP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/wrap/*.cpp)

# This library is mainly just for testing that the wrappers build.
add_library(android-jni-wrappers SHARED ${WRAP_SOURCES} ${JNIPP_ROOT}/jnipp.cpp)
target_include_directories(android-jni-wrappers PRIVATE "${JNIPP_ROOT}")
