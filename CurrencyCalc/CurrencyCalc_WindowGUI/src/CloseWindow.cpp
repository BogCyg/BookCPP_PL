// ==========================================================================
//
// Oprogramowanie napisane przez prof. Bogus�awa Cyganka do u�ytku z ksi��k�:
// ==> Programowanie w j�zyku C++. Wprowadzenie dla in�ynier�w. PWN 2023 <==
//
// Oprogramowanie jest dostarczane w stanie takim, w jakim jest, i do cel�w edukacyjnych
// bez �adnych gwarancji ani odpowiedzialno�ci za jego u�ycie w jakiejkolwiek aplikacji.
//
// ==========================================================================
//
// Software written by Boguslaw Cyganek (C) to be used with the book:
// INTRODUCTION TO PROGRAMMING WITH C++ FOR ENGINEERS
// Published by Wiley, 2020
//
// The software is supplied as is and for educational purposes
// without any guarantees nor responsibility of its use in any application. 
//
// ==========================================================================


#if _WIN32
	#include <windows.h>
#endif



#include "CloseWindow.h"




#if _WIN32


///////////////////////////////////////////////////////////
// This function closes the console window
///////////////////////////////////////////////////////////
//		
// INPUT:
//			none
//		
// OUTPUT:
//			none
//		
// REMARKS:
//		
//	
void CloseConsoleWindow( void )
{
	// Find a window and close it
	HWND h; 
	TCHAR szOldTitle[ MAX_PATH ]; 
	GetConsoleTitle( szOldTitle, MAX_PATH );
	h = FindWindow( NULL, szOldTitle );
	ShowWindow( h, SW_HIDE ); 
}

#else

void CloseConsoleWindow( void )
{
	// do we need it?

}

#endif





