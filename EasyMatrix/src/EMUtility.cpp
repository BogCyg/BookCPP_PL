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


// System headers in < >
#include <iostream>


// Own header in " "
#include "EMUtility.h"
#include "MarsXorShift.h"



#if EM_VER == 1


// -----------------------------------
// Input/output functions



// Poproś użytkownika o wprowadzenie wartości dla macierzy m 
// z klawiatury.
void AskUserForMatrixData( EMatrix & m )
{
	const Dim kCols = m.GetCols();
	const Dim kRows = m.GetRows();

	for( Dim r = 0; r < kRows; ++ r )
	{
		std::cout << "Enter data for row no. " << r << " of " << kRows << std::endl;
		for( Dim c = 0; c < kCols; ++ c )
		{
			std::cout << c << ": ";
			std::cin >> m.fData[ r ][ c ];		// odczytaj wartość z klawiatury
		}
	}
	std::cout << std::endl;	// znów nowa linia
}



// Wypisuje zawartość macierzy m na ekran
void ShowMatrix( const EMatrix & m )
{
	for( const auto & row : m.fData )	// przejdź wiersz po wierszu
	{
		for( const auto & data : row )	// przejdź po danych w pojedynczym wierszu
			std::cout << data << "\t";	// rozdziel dane za pomocą tabulatora

		std::cout << std::endl;		// wypisz nową linię
	}
	std::cout << std::endl;	// znów nowa linia
}





// -----------------------------------
// Math functions



// Dodaj dwie macierze, zwróć rezultat:
// c = a + b
// Wymiary macierzy a i b muszą być takie same.
EMatrix		AddMatrix( const EMatrix & a, const EMatrix & b )
{
	assert( a.GetRows() == b.GetRows() );	// sprawdź w wersji debug czy wymiary są takie same
	assert( a.GetCols() == b.GetCols() );

	EMatrix	c { a };	// Stwórz macierz c taką samą jak a

	for( Dim row = 0; row < b.GetRows(); ++ row )
		for( Dim col = 0; col < b.GetCols(); ++ col )
			c.fData[ row ][ col ] += b.fData[ row ][ col ];

	return c;
}

// Pomnóż dwie macierze, zwróć ich rezultat:
// c = a * b
// Wymiary a i b muszą być zgodne w przypadku mnożenia
EMatrix		MultMatrix( const EMatrix & a, const EMatrix & b )
{
	const auto a_cols = a.GetCols();
	const auto a_rows = a.GetRows();

	const auto b_cols = b.GetCols();
	const auto b_rows = b.GetRows();	

	assert( a_cols == b_rows );	// Wymiary muszą być takie same

	EMatrix	c( a_rows, b_cols, 0.0 );	// Macierz wynikowa ma takie rozmiary

	for( Dim ar = 0; ar < a_rows; ++ ar )	// Przejdź po wierszach macierzy a
		for( Dim bc = 0; bc < b_cols; ++ bc )	// Przejdź po kolumnach macierzy b
			for( Dim ac = 0; ac < a_cols; ++ ac ) // Przejdź po kolumnach a == wierszach b
				c.fData[ ar ][ bc ] += a.fData[ ar ][ ac ] * b.fData[ ac ][ bc ];

	return c;
}
	




// -----------------------------------
// Random init functions



// Does random initialization of a matrix m
void RandInit( EMatrix & m )
{
	MarsXorShift	randMachine;
	for( auto & row : m.fData )		// go row-by-row
		for( auto & data : row )	// go through the data in a single row
			data = randMachine.GetNext() & 0xFFFF;	// cast, type promotion
}





// ---------------------------------------------------------------


#else	// EM_VER > 1





// Overloaded operators 

// It can be used as follows: c = a + b;
EMatrix		operator + ( const EMatrix & a, const EMatrix & b )
{
	assert( a.GetRows() == b.GetRows() );	// dim must be the same
	assert( a.GetCols() == b.GetCols() );

	EMatrix	c { a };	// Make c the same as a

	for( Dim row = 0; row < b.GetRows(); ++ row )
		for( Dim col = 0; col < b.GetCols(); ++ col )
			c[ row ][ col ] += b[ row ][ col ];

	return c;
}

// It can be used as follows: c = a * b;
EMatrix		operator * ( const EMatrix & a, const EMatrix & b )
{
	const auto a_cols = a.GetCols();
	const auto a_rows = a.GetRows();

	const auto b_cols = b.GetCols();
	const auto b_rows = b.GetRows();	

	assert( a_cols == b_rows );	// Dimensions must be the same

	EMatrix	c( a_rows, b_cols, 0.0 );	// Output matrix has such dimensions

	for( Dim ar = 0; ar < a_rows; ++ ar )	// Traverse rows of a
		for( Dim bc = 0; bc < b_cols; ++ bc )	// Traverse cols of b
			for( Dim ac = 0; ac < a_cols; ++ ac ) // Traverse cols of a == rows of b
				c[ ar ][ bc ] += a[ ar ][ ac ] * b[ ac ][ bc ];

	return c;
}




// Does random initialization of a matrix m
void RandInit( EMatrix & m )
{
	MarsXorShift	randMachine;
	for( auto & row : m )			// go row-by-row
		for( auto & data : row )	// go through data in a single row
			data = randMachine.GetNext() & 0xFFFF;	// cast, type promotion
}


#endif




