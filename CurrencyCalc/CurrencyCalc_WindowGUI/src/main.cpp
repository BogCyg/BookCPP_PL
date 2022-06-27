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


#include <FL/FL_ask.H>
#include <filesystem>

#include "CurCalc_GUI.h"
#include "CloseWindow.h"



int main()
{
	CloseConsoleWindow();	// Pozbądź się okna konsoli

	namespace fs = std::filesystem;
	// Pozyskaj pełną ścieżkę do pliku inicjalizacji
	std::wstring iniPath( fs::current_path() / fs::path( CurrExchanger::initDefaultFileName ) );

	// Utwórz obiekt wymiany walut
	auto curExchObj = OL_CE::CreateCurExchanger( OL_CE::nbp_addr, iniPath );
	if( ! curExchObj )
		return fl_alert( "Cannot load currency information (no ini file, no Internet) - exiting ..." ), -1;	// Wyjdź

	// Utwórz obiekt GUI z dostarczonym obiektem wymiany walut
	CC_GUI	gCC_GUI( * curExchObj );		

	// Uruchom aplikację
	return gCC_GUI.Create_GUI();
}




