cmake_minimum_required( VERSION 3.9 )

# For a new project it is sufficient to change only its name in the following line
set( PROJECT_NAME ParallelCores )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )
#set( CMAKE_BUILD_TYPE Release )


if( WIN32 )
	set( CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /std:c++17 /D_UNICODE /DUNICODE /openmp" )
	set( CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1 /std:c++17 /D_UNICODE /DUNICODE /openmp" )
	message( "Win settings chosen..." )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall -fopenmp" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -Wall -fopenmp" )
	message( "Mac settings chosen..." )
elseif( UNIX )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall -fopenmp" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -Wall -fopenmp" )
	message( "Linux settings chosen..." )
endif()


# Inform CMake where the header files are
include_directories( include )


# Automatically add all *.cpp and *.h files to the project
file ( GLOB SOURCES "./src/*.cpp" "./include/*.h" )
add_executable( ${PROJECT_NAME} ${SOURCES} )


# Set the default project 
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )


if( UNIX )

	# The TBB library from Intel is need to execute std::execution::par in std::transform_reduce ...
	# You may need to install the TBB library (you see this if files compile OK, but there are linker errors)
	# sudo apt-get install libtbb-dev

	target_link_libraries( ${PROJECT_NAME} 	tbb  )

endif()


message( "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}" )
