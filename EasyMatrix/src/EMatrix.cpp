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



#include "EMatrix.h"
#include <iterator>
#include <string>
#include <sstream>





#if EM_VER > 1

// Prześlij matrix do strumienia wyjściowego. Zakładamy tu tryb tekstowy.
std::ostream & operator << ( std::ostream & out, const EMatrix & matrix )
{
	for( const auto & row : matrix/*.fData*/ )	// przejdź wiersz po wierszu
	{
		for( const auto & data : row )	// dane w pojedynczym wierszu
			out << data << "\t";

		out << std::endl;		
	}

	return out;		// zwróć strumień, aby można je było łączyć
}

// Pozyskaj matrix ze strumienia wejściowego. Zakładamy tu tryb tekstowy.
std::istream & operator >> ( std::istream & in, EMatrix & matrix )
{
	// Wymiary muszą być ustalone na podstawie układu danych.
	// Każda nowa linia stanowi nowy wiersz macierzy.
	// Musimy więc odczytywać ciągi znaków wiersz po wierszu, 
	// a z każdego ciągu czytać kolejno dane.

	matrix.fData.clear();		// pozbądź się tego, co tam było

	std::string str;	// pusty ciąg znaków
	while( getline( in, str ) )	// wczytaj całą linię do ciągu znaków
	{
		// Utwórz strumień ciągów znaków z ciągu znaków
		std::istringstream istr( str );

#define SIMPLE 1
#if SIMPLE 

		DataType	data {};		// dane tymczasowe
		RealVec		one_row;		// najpierw utwórz pusty wiersz
		while( istr >> data )		// wczytaj ze strumienia do data
			one_row.push_back( data );	// wypełnij jeden wiersz

		matrix.fData.emplace_back( one_row );	// umieść wiersz w macierzy

#else
		using DType_Iter = std::istream_iterator< DataType >;

		// Tutaj przenosimy 
		matrix.fData.emplace_back(	std::make_move_iterator( DType_Iter{ istr } ), 
									std::make_move_iterator( DType_Iter{} ) );

#endif

	}

	return in;		// zwróć strumień, aby można je było łączyć
}




	// Let add some overloaded arithmetical operators
	EMatrix &		EMatrix::operator += ( const EMatrix & b )	
	{
		assert( GetRows() == b.GetRows() );	// dim must be the same
		assert( GetCols() == b.GetCols() );

		for( Dim row = 0; row < b.GetRows(); ++ row )
			for( Dim col = 0; col < b.GetCols(); ++ col )
				fData[ row ][ col ] += b[ row ][ col ];

		return * this;	
	}

	EMatrix			EMatrix::operator + ( const EMatrix & b ) const
	{
		// Where does matrix "a" come from? It is "this".
		assert( GetRows() == b.GetRows() );	// dim must be the same
		assert( GetCols() == b.GetCols() );

		EMatrix	c { * this };	// Make c the same as a

		c += b;		// call the add and assing operator +=

		return c;	
	}




#endif






#if 0


// Stream in a matrix from i.
// Assume text mode.
std::istream & operator >> ( std::istream & i, EMatrix & matrix )
{
	// Dimensions have to be determined from the data layout.
	// Each new line constitutes a new row of a matrix.
	// So, we have to read strings line by line, and
	// from each string read item by data item.

	matrix.GetMatrixData().clear();		// get rid of whatever was there
	
	for( std::string str; getline( i, str ); )
	{
		// Create a string-stream from a string
		std::istringstream istr( str );

		using DType_Iter = std::istream_iterator< DataType >;

		// Here we move 
		matrix.fData.emplace_back(	std::make_move_iterator( DType_Iter{ istr } ), 
									std::make_move_iterator( DType_Iter{} ) );
	}

	return i;
}


#endif












