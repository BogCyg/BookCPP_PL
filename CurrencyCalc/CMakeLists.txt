cmake_minimum_required( VERSION 3.6.2 )

# For a new project it is sufficient to change only its name in the following line
set( PROJECT_NAME CurrencyCalcProject )

project( ${PROJECT_NAME} )



set( CMAKE_BUILD_TYPE Debug )
#set( CMAKE_BUILD_TYPE Release )


# Recurse into the subdirectories. CMake will walk through
# the project's entire directory structure.

add_subdirectory  	( CurrencyCalc_Lib			CurrencyCalc_Lib/build 			)
add_subdirectory 	( CurrencyCalc_Terminal		CurrencyCalc_Terminal/build 	)
add_subdirectory 	( CurrencyCalc_WindowGUI	CurrencyCalc_WindowGUI/build 	)

set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT CurrencyCalc_WindowGUI ) # Set the default project 



