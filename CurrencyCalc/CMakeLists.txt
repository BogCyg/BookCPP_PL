cmake_minimum_required( VERSION 3.6.2 )

# For a new project it is sufficient to change only its name in the following line
set( PROJECT_NAME CurrencyCalcProject )

project( ${PROJECT_NAME} )



set( CMAKE_BUILD_TYPE Debug )
#set( CMAKE_BUILD_TYPE Release )


# Recurse into the subdirectories. CMake will walk through
# the project's entire directory structure.



if( WIN32 )
	add_subdirectory  	( CurrencyCalc_Lib		CurrencyCalc_Lib/build_win 		)
	add_subdirectory 	( CurrencyCalc_Terminal		CurrencyCalc_Terminal/build_win 	)
	add_subdirectory 	( CurrencyCalc_WindowGUI	CurrencyCalc_WindowGUI/build_win 	)
	set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CurrencyCalc_WindowGUI ) # Set the default project 
	message( "Win settings chosen..." )
elseif( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
	add_subdirectory  	( CurrencyCalc_Lib		CurrencyCalc_Lib/build_mac 		)
	add_subdirectory 	( CurrencyCalc_Terminal		CurrencyCalc_Terminal/build_mac 	)
	add_subdirectory 	( CurrencyCalc_WindowGUI	CurrencyCalc_WindowGUI/build_mac 	)
	message( "Mac settings chosen..." )
elseif( UNIX )
	add_subdirectory  	( CurrencyCalc_Lib		CurrencyCalc_Lib/build_linux 		)
	add_subdirectory 	( CurrencyCalc_Terminal		CurrencyCalc_Terminal/build_linux 	)
	add_subdirectory 	( CurrencyCalc_WindowGUI	CurrencyCalc_WindowGUI/build_linux 	)
	message( "Linux settings chosen..." )
endif()