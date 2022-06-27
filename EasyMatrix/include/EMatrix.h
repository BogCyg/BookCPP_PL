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

// Alias typu dla wektora wymiarów (rozmiar)
using Dim		= RealVec::size_type;

// Alias typu dla wektora typów (np. double)
using DataType	= RealVec::value_type;


// // Alias typu dla wektora wektorów wartości double = macierz rzeczywista
using RealMatrix = std::vector< RealVec >;



// ----------------------------------------
// Part II

#include <cassert>

// Set to 1 for FIRST simple version
// Set to 2 for the SECOND object-oriented version
#define EM_VER 2


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

	RealMatrix	fData;	// data structure (encapsulation)

public:

	// A parametric constructor
	EMatrix( Dim rows, Dim cols, DataType initVal = 0.0 )
		: fData( rows, RealVec( cols, initVal ) )
	{	// matrix == a vector of vectors of double
		assert( cols > 0 );
		assert( rows > 0 );
	}


	// Helpers
	auto	GetCols( void ) const { return fData[ 0 ].size(); }
	auto	GetRows( void ) const { return fData.size(); }


	// -----------------------------------------------------------
	// Ver. 2.0

	// As a result of overloaded subscript operators 
	// instead of m.fData[2][3] we can write directly m[2][3] 
	auto &			operator[] ( Dim idx ) { return fData[ idx ]; }			
	const auto &	operator[] ( Dim idx ) const { return fData[ idx ]; }

	// We need only these two pairs of functions to have a range-based for loop
	auto			begin() { return fData.begin(); }
	auto			end()	{ return fData.end(); }

	auto			begin() const { return fData.begin(); }
	auto			end()	const { return fData.end(); }




	// Let add some overloaded arithmetical operators
	EMatrix &		operator += ( const EMatrix & b );	// this will probably change this object
	EMatrix			operator + ( const EMatrix & b ) const;
	// We can add other operators here ...


	// friends are functions that can freely access fData
	friend std::ostream & operator << ( std::ostream & o, const EMatrix & matrix );
	friend std::istream & operator >> ( std::istream & i, EMatrix & matrix );


};






// ----------------------------------------
// Part III

EMatrix		operator + ( const EMatrix & a, const EMatrix & b );

EMatrix		operator * ( const EMatrix & a, const EMatrix & b );





#endif




