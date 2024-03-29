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






// ----------------------------------------
// Part I

#include <iostream> 
#include <vector>







// Deklaracja aliasu typu dla wektora wartości double (przybliżenie liczb rzeczywistych)
using RealVec = std::vector< double >;

// Alias typu dla rozmiarów wektora (rozmiar)
using Dim		= RealVec::size_type;

// Alias dla typu przechowywanych obiektów w wektorze (np. double)
using DataType	= RealVec::value_type;


// // Alias typu dla wektora wektorów wartości double = macierz rzeczywista
using RealMatrix = std::vector< RealVec >;



// ----------------------------------------
// Part II

#include <cassert>

// Set to 1 for FIRST simple version
// Set to 2 for the SECOND object-oriented version
#define EM_VER 1


#if EM_VER == 1


// -----------------------------------------------------------
// Ver. 1.0



// EMatrix jest opakowaniem dla obiektu RealMatrix. 
// Rolą otoki jest dostarczenie pewnych akcji.
struct EMatrix
{


	RealMatrix	fData;	// struktura danych


	// Konstruktor parametryczny
	// rows, cols – liczba wierszy i kolumn macierzy (powinny być > 0)
	// initVal – wartość początkowa elementów macierzy
	EMatrix( Dim rows, Dim cols, DataType initVal = 0.0 )
		: fData( rows, RealVec( cols, initVal ) )
	{	
		// macierz == wektor wektorów typu double
		assert( cols > 0 );
		assert( rows > 0 );
	}


	// Funkcje pomocnicze
	auto	GetCols( void ) const { return fData[ 0 ].size(); }
	auto	GetRows( void ) const { return fData.size(); }

};

#else



// -----------------------------------------------------------
// Ver. 2.0



class EMatrix
{
	// -----------------------------------------------------------
	// Ver. 1.0

private:

	RealMatrix	fData;	// prywatna struktura danych (hermetyzacja)

public:

	// Konstruktor parametryczny - rows oraz cols powinny być > 0
	EMatrix( Dim rows, Dim cols, DataType initVal = 0.0 )
		: fData( rows, RealVec( cols, initVal ) )
	{	// macierz == wektor wektorów danych typu double
		assert( cols > 0 );
		assert( rows > 0 );
	}


	// Funkcje pomocnicze
	auto	GetCols( void ) const { return fData[ 0 ].size(); }
	auto	GetRows( void ) const { return fData.size(); }


	// -----------------------------------------------------------
	// Ver. 2.0

	// Z powodu przeciążonych operatorów indeksu 
	// zamiast m.fData[2][3] możemy napisać bezpośrednio m[2][3] 
	auto &			operator[] ( Dim idx ) { return fData[ idx ]; }			
	const auto &	operator[] ( Dim idx ) const { return fData[ idx ]; }

	// Potrzebujemy tylko tych dwóch par funkcji do uzyskania zakresowej pętli for
	auto			begin() { return fData.begin(); }
	auto			end()	{ return fData.end(); }

	auto			begin() const { return fData.begin(); }
	auto			end()	const { return fData.end(); }




	// Dodajmy pewne przeciążone operatory arytmetyczne
	EMatrix &		operator += ( const EMatrix & b );	// to może zmienić ten obiekt
	EMatrix			operator + ( const EMatrix & b ) const;
	// Tutaj możemy dodać inne operatory...


	// Funkcje zaprzyjaźnione mogą uzyskiwać swobodny dostęp do fData
	friend std::ostream & operator << ( std::ostream & o, const EMatrix & matrix );
	friend std::istream & operator >> ( std::istream & i, EMatrix & matrix );


};






// ----------------------------------------
// Part III

EMatrix		operator + ( const EMatrix & a, const EMatrix & b );

EMatrix		operator * ( const EMatrix & a, const EMatrix & b );





#endif




