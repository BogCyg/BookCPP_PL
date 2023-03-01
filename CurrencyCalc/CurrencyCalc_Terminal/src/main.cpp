// ==========================================================================
//
// Oprogramowanie napisane przez prof. Bogusława Cyganka do użytku z książką:
// ==> Programowanie w języku C++. Wprowadzenie dla inżynierów. PWN 2023 <==
//
// Oprogramowanie jest dostarczane w stanie takim, w jakim jest, i do celów edukacyjnych
// bez żadnych gwarancji ani odpowiedzialności za jego użycie w jakiejkolwiek aplikacji.
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





#include <filesystem>
#include <fcntl.h>


#include "CurrencyCalcPlayGround.h"



#include <iostream>
#include <locale>

// Twórz prosty main(), kod umieść w innych komponentach
int main()
{
	setlocale( LC_CTYPE, "pl_PL.utf8" );
	CurrExchanger::OnLine_CurrExchanger::Run();
	return 0; // Choć nie jest to wymagane, zwróć wartość z main
}






