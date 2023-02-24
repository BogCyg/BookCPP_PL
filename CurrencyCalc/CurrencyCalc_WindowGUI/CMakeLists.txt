cmake_minimum_required( VERSION 3.6.2 )

# For a new project it is sufficient to change only its name in the following line
set( PROJECT_NAME CurrencyCalc_WindowGUI )

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
	set( CMAKE_CXX_FLAGS "-std=c++17 -Wall -pthread" )
	set( CMAKE_CXX_FLAGS_DEBUG "-g -Og -std=c++17 -Wall -pthread" )
	message( "Linux settings chosen..." )
endif()




# Inform CMake where the header files are
include_directories( ../CurrencyCalc_Lib/include )
include_directories( ./include )
include_directories( ../../FLTK )
#include_directories( ../../FLTK/build/FL )		# added in 2023 after FLTK changed to GitHub
file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/../../FLTK/build/FL/fl_config.h DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/../../FLTK/FL )


# Automatically add all *.cpp files to the project
file ( GLOB SOURCES "./src/*.cpp" )

# Add source file to the build executable
add_executable( ${PROJECT_NAME} ${SOURCES} )


# Some system libraries
if( WIN32 )

# Assuming Windows SDK is installed, so we do not need to call find_library()

	target_link_libraries( 	${PROJECT_NAME} 
				PUBLIC 
					wsock32
					comctl32
					gdiplus.lib
					gdi32.lib
					user32.lib
			)

	# FLTK libraries
	find_library( 	FLTK_LIBRARY
			NAMES 			fltkd fltk	fltk_formsd fltk_gld fltk_gl 	libfltk libfltk_forms
			#PATHS 			../../FLTK/lib/Debug 	../../FLTK/lib/Release 	../../FLTK/lib )
			PATHS 			../../FLTK/build/lib/Debug 	../../FLTK/build/lib/Release 	../../FLTK/build/lib )	# changed in 2023 after FLTK changed to GitHub

	target_link_libraries( 	${PROJECT_NAME} 
			PUBLIC 
				CurrencyCalc_Lib
				${FLTK_LIBRARY} 
		)

		
	# Set the default project 
	set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} )


elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")

	find_library( COCOA_LIB Cocoa )
	target_link_libraries( ${PROJECT_NAME} PUBLIC ${COCOA_LIB} )


elseif( UNIX )


	# FLTK libraries
	find_library( 	FLTK_LIBRARY
			NAMES 			fltk	fltk_forms  fltk_images 	
			PATHS 			../../FLTK/build/lib )	

	# https://www.fltk.org/doc-1.3/basics.html		
	#-L/usr/local/lib -lfltk -lXext -lX11 -lm

	find_library( 	SYSTEM_LIBRARY
			NAMES 			Xext	X11		m	dl	l 	OpenGL	pthread
			PATHS 			/usr/local/lib )	
	

	target_link_libraries( 	${PROJECT_NAME} 
			PUBLIC 
				CurrencyCalc_Lib
				${FLTK_LIBRARY} 
				${SYSTEM_LIBRARY} 		
				"/usr/lib/x86_64-linux-gnu/libdl.so"
				)	

endif()




message( "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}" )



