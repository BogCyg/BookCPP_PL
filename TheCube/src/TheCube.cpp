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




#include "TheCube.h"







#include <iostream>
#include <fstream>
#include <cassert>





std::ostream & operator << ( std::ostream & o, const TheCube & cube )
{
	// Wypisz dane jako strumienie binarne
	o.write(	reinterpret_cast< const char * >(  & cube.fDim[ 0 ] ), 
		sizeof( cube.fDim ) );		// sizeof zwraca rozmiar całej tablicy 
	o.write(	reinterpret_cast< const char * >(  cube.fDataBuf.get() ), 
		cube.Size() * sizeof( TheCube::value_type ) );
	return o;
}


std::istream & operator >> ( std::istream & i, TheCube & cube )
{
	// Najpierw odczytaj wymiary
	i.read( reinterpret_cast< char * >( & cube.fDim[ 0 ] ), sizeof( cube.fDim ) );	
	if( i )		// sprawdź, czy strumień jest OK
	{
		cube.fDataBuf = std::make_unique< TheCube::value_type [] >( cube.Size() );

		const auto cube_bytes = cube.Size() * sizeof( TheCube::value_type );
		// read() przyjmuje liczbę bajtów
		i.read( (char*)cube.fDataBuf.get(), cube_bytes );	// Odczytaj resztę danych 

		assert( i );
	}
	return i;
}







