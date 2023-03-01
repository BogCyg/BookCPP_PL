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


#include <iomanip>

#include "Currency.h"



namespace CppBook
{



// "w" dla strumieni znaków dwubajtowych
std::wostream & operator << ( std::wostream & o, const TCurrency & c )
{
	const int kOutWidth { 10 };		// całkowita szerokość wyjścia numerycznego
	const int kOutPrec { 4 };		// precyzja dla kursów

	o << c.GetCurrKey() << "\t";
	o << c.GetCurrName() << "\t";

	o	<<	std::fixed 
		<<	std::setw( kOutWidth ) 
		<<	std::setprecision( kOutPrec ) 
		<<	c.GetSellRate() << "\t";

	o	<<	std::fixed 
		<<	std::setw( kOutWidth ) 
		<<	std::setprecision( kOutPrec ) 
		<< c.GetBuyRate()  << "\t";

	return o;
}

std::wistream & operator >> ( std::wistream & i, TCurrency & c )
{
	wstring s {};	// pusty tymczasowy ciąg znaków
	i >> s; c.SetCurrCode( s );
	i >> s; c.SetCurrName( s );

	double tmp {};	// tymczasowa zmienna typu double
	i >> tmp; c.SetSellRate( tmp );
	i >> tmp; c.SetBuyRate( tmp );

	return i;
}



}	// CppBook

