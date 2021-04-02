cmake_minimum_required(VERSION 3.10)

# set the project name
project(Mecab_window)
set(CMAKE_FINAL_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/exe)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_FINAL_OUTPUT_DIRECTORY}>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_FINAL_OUTPUT_DIRECTORY}>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_FINAL_OUTPUT_DIRECTORY}>)


# 複製整個mecab資料夾
file(GLOB MECAB mecab/*)
file(COPY ${MECAB} DESTINATION ${CMAKE_SOURCE_DIR}/build/exe)


# 連結資料夾
link_directories(./mecab)
#編譯內容
add_executable(Mecab_window main.cpp)

# 連結lib
target_link_libraries(Mecab_window libmecab)