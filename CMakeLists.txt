cmake_minimum_required(VERSION 3.24)
project(playingCardsLib)

set(CMAKE_CXX_STANDARD 17)

add_executable(playingCardsLib main.cpp)
add_executable(deck_lib_test deck_lib_test.cpp)
add_library(deck_lib SHARED deck_lib.cpp deck_lib.h)

find_library(DECK_LIBRARY lib)
target_link_libraries(playingCardsLib LINK_PUBLIC ${PROJECT_SOURCE_DIR}/lib/libdeck_lib.so)
target_link_libraries(deck_lib_test LINK_PUBLIC ${PROJECT_SOURCE_DIR}/lib/libdeck_lib.so)
