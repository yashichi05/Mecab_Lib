cmake_minimum_required(VERSION 3.10)
# set the project name

project(Mecab_window)

set(CMAKE_FINAL_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/dist)
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

add_executable(test test.cpp)

# 連結資料夾
link_directories(mecab)

# 複製整個mecab資料夾
file(GLOB MECAB mecab/*)
file(COPY ${MECAB} DESTINATION ${CMAKE_SOURCE_DIR}/dist)

add_library(testmecab MODULE testmecab.cpp ExtensionImpl.cpp)
# 連結lib
target_link_libraries(testmecab libmecab Qt5::Widgets)

#編譯內容
if (NOT EXISTS ${CMAKE_FINAL_OUTPUT_DIRECTORY}/Qt5WebSockets.dll AND NOT EXISTS ${CMAKE_FINAL_OUTPUT_DIRECTORY}/Qt5WebSocketsd.dll)
    add_custom_command(TARGET testmecab
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/windeployqt"
        COMMAND set PATH=%PATH%$<SEMICOLON>${qt5_install_prefix}/bin
        COMMAND Qt5::windeployqt --dir ${CMAKE_FINAL_OUTPUT_DIRECTORY} "${CMAKE_FINAL_OUTPUT_DIRECTORY}/testmecab.dll"
    )
endif() 