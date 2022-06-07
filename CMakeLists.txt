cmake_minimum_required(VERSION 3.16)
project(SpiceCPP)

set(CMAKE_CXX_STANDARD 20)

add_executable(SpiceCPP main.cpp spiceLexer.cpp spiceLexer.h lexerToken.cpp lexerToken.h spiceParser.cpp spiceParser.h spiceASTNode.cpp spiceASTNode.h)
