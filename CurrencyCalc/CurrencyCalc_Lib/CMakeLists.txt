cmake_minimum_required( VERSION 3.6.2 )

# For a new project it is sufficient to change only its name in the following line
set( PROJECT_NAME CurrencyCalc_Lib )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug )
#set( CMAKE_BUILD_TYPE Release )



if( WIN32 )
	set( CMAKE_CXX_FLAGS "/DWIN32 /D_WINDOWS /W3 /GR /EHsc /std:c++17 /D_UNICODE /DUNICODE" )
	set( CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1 /std:c++17 /D_UNICODE /DUNICODE" )
	message( "Win settings chosen..." )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -Og -std=c++17 -Wall" )
	message( "Mac settings chosen..." )
elseif( UNIX )
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -Og -std=c++17 -Wall" )
	message( "Linux settings chosen..." )
endif()


# Inform CMake where the header files are
include_directories( include )


# Automatically add all *.cpp and *.h files to the project
file ( GLOB SOURCES "./src/*.cpp" "./include/*.h" )




# This works
#set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib )



#add_executable( ${PROJECT_NAME} ${SOURCES} )
add_library( ${PROJECT_NAME} STATIC ${SOURCES} )


# Make sure the compiler can find include files for the library
# when other libraries or executables link to this one
target_include_directories ( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include )


# On Linux we need CURL library for the Internet connection
if( UNIX )

	find_package( CURL REQUIRED ) 									# first find it

	if( CURL_FOUND )
		message( "CURL found and linked" )
		include_directories( ${CURL_INCLUDE_DIR} )						# add CURL's include dir
		target_link_libraries( ${PROJECT_NAME} ${CURL_LIBRARIES} )		# link to the CURL library
	elseif()
		message( "Cannot find CURL - try to install and try again" )
		# sudo apt-get install curl
		# sudo apt-get install libssl-dev libcurl4-openssl-dev
	endif()


endif()



# INSTALL(
#   	TARGETS ${PROJECT_NAME}
#   	ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib
#   	LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/lib
#   	COMPONENT library
# )


#set( CMAKE_VS_INCLUDE_INSTALL_TO_DEFAULT_BUILD 1 )


message( "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}" )




