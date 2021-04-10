cmake_minimum_required(VERSION 3.10)
cmake_policy(SET CMP0037 OLD)
# set the project name

project(Mecab_window)

set(CMAKE_FINAL_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/exe)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_FINAL_OUTPUT_DIRECTORY}>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_FINAL_OUTPUT_DIRECTORY}>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_FINAL_OUTPUT_DIRECTORY}>)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(QtUtils)
msvc_registry_search()
find_qt5(Core Widgets WebSockets)


add_compile_options(
  /std:c++17
  /MP
  /wd4018 # signed/unsigned mismatch
  /DUNICODE # config.pri
  /D_UNICODE
)


# 連結資料夾
link_directories(mecab)

# 複製整個mecab資料夾
file(GLOB MECAB mecab/*)
file(COPY ${MECAB} DESTINATION ${CMAKE_SOURCE_DIR}/build/exe)

add_library(mecabWindow\ Extension SHARED mecabWindow.cpp ExtensionImpl.cpp)
add_library(visual\ Extension SHARED VisualExtension.cpp ExtensionImpl.cpp)
# 連結lib
target_link_libraries(mecabWindow\ Extension libmecab Qt5::Widgets)


#編譯內容
add_executable(test test.cpp)