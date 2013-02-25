cmake_minimum_required(VERSION 2.6)

include_directories(${GTKMM_INCLUDE_DIRS})
link_directories(${GTKMM_LIBRARY_DIRS})

add_executable(single
	hello.cpp
	)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

target_link_libraries( single ${GTKMM_LIBRARIES})

