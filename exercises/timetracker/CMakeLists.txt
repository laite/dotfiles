cmake_minimum_required(VERSION 2.6)
find_package(Boost 1.49.0 COMPONENTS system filesystem)

include_directories( ${GTKMM_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
link_directories( ${GTKMM_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})

add_executable(timetracker
	config.cpp
	config.h 
	data.cpp
	data.h 
	log.cpp
	log.h 
	main.cpp
	treedata.cpp
	treedata.h
	window.cpp
	window.h 
	)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

target_link_libraries( timetracker ${Boost_LIBRARIES} ${GTKMM_LIBRARIES})

