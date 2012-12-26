link_directories( ${GTKMM_LIBRARY_DIRS} )

include_directories( ${GTKMM_INCLUDE_DIRS} )

add_executable(example
	main.cpp
	log.cpp
	log.h 
	window.cpp
	window.h 
	treedata.cpp
	treedata.h
	data.cpp
	data.h )

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

target_link_libraries( example
	${GTKMM_LIBRARIES} )
