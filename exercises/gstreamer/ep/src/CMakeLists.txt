cmake_minimum_required(VERSION 2.6)

find_package(Boost 1.49.0 COMPONENTS system filesystem)
find_library(TAGLIB_LIB tag)

include_directories(${GTKMM_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} /usr/include/taglib/)
link_directories(${GTKMM_LIBRARY_DIRS}${Boost_LIBRARY_DIRS})

add_executable(
	ep
	backend.cpp backend.h
	config.cpp config.h
	engine.cpp engine.h
	global.cpp global.h
	library.cpp library.h
	main.cpp
	playback.cpp playback.h
	playlist.cpp playlist.h
	song.cpp song.h
	widget.cpp widget.h
	window.cpp window.h
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

target_link_libraries( ep ${Boost_LIBRARIES} ${GTKMM_LIBRARIES} ${TAGLIB_LIB})

