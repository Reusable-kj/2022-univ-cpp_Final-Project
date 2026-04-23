cmake_minimum_required(VERSION 3.10)
project(CardGame)

set(CMAKE_CXX_STANDARD 17)

# MSVC 인코딩 경고 방지 (CP949/UTF-8 호환)
if(MSVC)
    add_compile_options(/utf-8)
endif()

# 헤더 파일 경로 지정
include_directories(include)

# 실행 파일 생성
add_executable(CardGame src/card_game.cpp)
