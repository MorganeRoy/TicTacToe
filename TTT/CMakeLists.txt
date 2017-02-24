cmake_minimum_required(VERSION 3.0.2)

project(AI_Class)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/CMakeModules")

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
  add_compile_options(-std=c11 -Wall)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-std=c11 -Wall)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/W4)
endif()

set(src_dir ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(sources
    ${src_dir}/main.c
    ${src_dir}/jeu.c
    ${src_dir}/jeu.h
    ${src_dir}/alphabeta.c
    ${src_dir}/alphabeta.h)

add_executable(TTT ${sources})