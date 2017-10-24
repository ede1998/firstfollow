cmake_minimum_required(VERSION 3.7)
project(firstfollow)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AST.cpp AST.h Lexer.h Parser.h)
add_executable(firstfollow ${SOURCE_FILES})