#===============================================================================
#
# Copyright (C) 2020 Istituto Italiano di Tecnologia (IIT)
#
# This software may be modified and distributed under the terms of the
# GPL-2+ license. See the accompanying LICENSE file for details.
#
#===============================================================================

cmake_minimum_required(VERSION 3.12)

project(TestRendering LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

set(TEST_TARGET_NAME test-rendering)

find_package(OpenCV REQUIRED)

find_package(SuperimposeMesh REQUIRED)

enable_testing()

add_executable(${TEST_TARGET_NAME} test/test-rendering/main.cpp)

target_link_libraries(${TEST_TARGET_NAME} PRIVATE ${OpenCV_LIBS} SI::SuperimposeMesh)

add_test(NAME ${TEST_TARGET_NAME}
         COMMAND ${TEST_TARGET_NAME} ${PROJECT_SOURCE_DIR}/assets/obj_000005.obj ${PROJECT_SOURCE_DIR}/assets/ground_truth.png
         WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_TARGET_NAME}>
)
