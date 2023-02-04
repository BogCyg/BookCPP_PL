cmake_minimum_required( VERSION 3.14 )

# For a new project it is sufficient to change only its name in the following line
# This project relies on the RomanApp project
set( PROJECT_NAME RomanApp_GTest )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )
#set( CMAKE_BUILD_TYPE Release )



if( WIN32 )
	set( CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /std:c++17 /D_UNICODE /DUNICODE" )
	set( CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1 /std:c++17 /D_UNICODE /DUNICODE" )
	message( "Win settings chosen..." )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -Wall" )
	message( "Mac settings chosen..." )
elseif( UNIX )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -std=c++17 -Wall" )
	message( "Linux settings chosen..." )
endif()



# Inform CMake where the header files are
include_directories( include "../RomanApp/include" )


# Automatically add all *.cpp and *.h files to the project
file ( GLOB SOURCES "./src/*.cpp" "./include/*.h" )
add_executable( ${PROJECT_NAME} ${SOURCES} "../RomanApp/src/Dec2Roman.cpp" )

target_link_libraries( ${PROJECT_NAME} GTest::gtest_main )



# ---------------------------------------------------------
# Add GTest framework
# https://google.github.io/googletest/quickstart-cmake.html

include(FetchContent)
FetchContent_Declare(  	googletest
  			URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
		    )
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include( GoogleTest )
gtest_discover_tests( ${PROJECT_NAME} )
# ---------------------------------------------------------



# Set the default project 
set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )


message( "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}" )
