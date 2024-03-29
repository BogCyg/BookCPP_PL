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


#include <iostream>
#include <cassert>
#include <cmath>

using std::log;


void LongNumbers_Test( void );
void LongNumbersWithProxy_Test( void );

void Derived_PESEL_Test( void );
void Embedded_PESEL_Test( void );

int main()
{
	std::cout << "Good day!" << std::endl;

	// ------------------------------------
	// Test PESEL ID stored in unsigned int
	using ID_TYPE = unsigned long;
	ID_TYPE		fID {};		// PESEL id

	std::cout << "sizeof( ID_TYPE ) = " << sizeof( ID_TYPE ) << std::endl;
	std::cout	<< "Bits to store 11 digits = " << (int) ( log( 99999999999.0 ) / log( 2.0 ) ) + 1;
	
	fID = 94120612345;
	std::cout << "\nfID = " << fID << std::endl;
	// ------------------------------------


	LongNumbers_Test();

	Derived_PESEL_Test();
	Embedded_PESEL_Test();

	LongNumbersWithProxy_Test();

	return 0;
}

// -------------------------------------------------



class _TPerson
{
private:

	std::wstring		fFirstName;
	std::wstring		fLastName;

	unsigned char		fAge {};

	unsigned int		fID {};		// PESEL id - capacity problem here ...

public:

	// ...
};



// -------------------------------------------------
// Use "stronger" types

#include "Embedded_PESEL.h"



class TAge
{
	unsigned char fAge {};

public:

	TAge( unsigned char age = 0 ) : fAge( age ) {}

	auto GetAge( void ) const { return fAge; }

	// Sprawdza warunek wstępny odnośnie tego, co jest zapisywane
	void SetAge( unsigned char age ) { assert( age < 128 ); fAge = age; }

	// ... więcej interfejsu
};



class TPerson
{
private:

	std::wstring		fFirstName;
	std::wstring		fLastName;

	TAge				fAge {};		// Samowystarczalna klasa do reprezentowania wieku

	PESEL				fID {};		// numer PESEL – nie ma tu problemu z pojemnością

public:

	// ...
};



// -------------------------------------------------




