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


// System headers in < >
#include <iostream>
#include <fstream>


// Own header in " "
#include "EMUtility.h"
#include "MarsXorShift.h"




// Here we show hot to use "raw" RealMatrix
void Easy_Matrix_First_Test( void )
{

	// -------------------------
	// Korzystanie z RealMatrix w bieżącej postaci

	RealMatrix		m = {
							{ 2, 2, 0, 11 },
							{ 3, 4, 5, 0 },
							{ -1, 2, -1, 7 }
						};

	// Dodaj kolejny wiersz
	m.push_back( { 5, 3, 5, -3 } );

	// Posumuj elementy z wyjątkiem diagonali
	double non_diagonal_sum {};

	for( Dim r = 0; r < m.size(); ++ r )
		for( Dim c = 0; c < m[ 0 ].size(); ++ c )
			if( c != r )
				non_diagonal_sum += m[ r ][ c ];

	std::cout << "Sum of m except the diagonal " << non_diagonal_sum << std::endl;


}




#if EM_VER == 1


// Aby użyć jakiejś funkcji, musimy jedynie podać jej deklarację.
// Żeby jednak napisać pełny program, definicja funkcji musi
// zostać dodana w którymś z plików źródłowych.
void		AskUserForMatrixData( EMatrix & m );
void		ShowMatrix( const EMatrix & m );
EMatrix		MultMatrix( const EMatrix & a, const EMatrix & b );




// Tutaj pokazujemy, jak używać EMatrix
void Easy_Matrix_Second_Test( void )
{
	std::cout << "--------------------------------------------------------------" << std::endl;
	std::cout << "In this example we will:" << std::endl;
	std::cout << "* Create a 3x4 matrix M1 (you will be asked to enter its data)" << std::endl;
	std::cout << "* Print M1" << std::endl;
	std::cout << "* Create a 4x2 matrix M2 (you will be asked to enter its data)" << std::endl;
	std::cout << "* Print M2" << std::endl;
	std::cout << "* Compute and print a product M1 * M2" << std::endl;
	std::cout << "--------------------------------------------------------------" << std::endl;


	EMatrix		matrix_1( 3, 4 );
	AskUserForMatrixData( matrix_1 );

	std::cout << "You've just entered M1 - is it correct?" << std::endl;
	ShowMatrix( matrix_1 );


	EMatrix		matrix_2( 4, 2 );
	AskUserForMatrixData( matrix_2 );

	std::cout << "You've just entered M2 - is it correct?" << std::endl;
	ShowMatrix( matrix_2 );


	std::cout << "The matrix product of M1 * M2 is:" << std::endl;
	ShowMatrix( MultMatrix( matrix_1, matrix_2 ) );



}





#else // EM_VER > 1


// Pokazujemy tu jak strumieniować obiekty EMatrix w obie strony 
void Easy_Matrix_Third_Test( void )
{
	EMatrix	matrix_1( 3, 3 );

	RandInit( matrix_1 );


	{
		std::cout << matrix_1;	// prześlij strumieniem na ekran	
		
		std::ofstream oma( "ema.txt" );

		oma << matrix_1;	// tym samym operatorem << prześlij strumieniem do pliku
	}

	{
		EMatrix matrix_2( 1, 1 );	// musi istnieć co najmniej 1 element

		std::ifstream ima( "ema.txt" );

		ima >> matrix_2;			// Pobierz ze strumienia z pliku wejściowego

		std::cout << std::endl << matrix_2 << std::endl;		// pokaż na ekranie
	}


	// Z przeciążonymi operatorami operacje są jeszcze prostsze
	//std::cout << "M1 + M1 = \n" << matrix_1 + matrix_1 << std::endl;	// 'operator +' jest dwuznaczny
	std::cout << "M1 + M1 = \n" << matrix_1.operator + ( matrix_1 ) << std::endl;	
	std::cout << "M1 * M1 = \n" << matrix_1 * matrix_1 << std::endl;

}


// Here we show hot to stream out and in EMatrix objects
void Easy_Matrix_Fourth_Test(void)
{
	EMatrix	matrix_1( 200, 200 ), matrix_2( 200, 200 );

	RandInit( matrix_1 );
	RandInit( matrix_2 );

	EMatrix	matrix_3( matrix_1.operator + ( matrix_1 ) );

	EMatrix	matrix_4( matrix_1 * matrix_2 );

	std::cout << matrix_3[10][20] << std::endl;
	std::cout << matrix_4[10][20] << std::endl;


	// With overloaded operators operations are even easier
	//std::cout << "M1 + M1 = \n" << matrix_1 + matrix_1 << std::endl;	// 'operator +' is ambiguous
	//std::cout << "M1 + M1 = \n" << matrix_1.operator + (matrix_1) << std::endl;
	//std::cout << "M1 * M1 = \n" << matrix_1 * matrix_1 << std::endl;

}


void Easy_Matrix_Zeroth_Test( void )
{
	EMatrix		m ( 2, 3 );
	std::cin >> 	m; 		// Wywołaj operator wyodrębniania na std::cin i m
	std::cout << 	m; 		// Wywołaj operator wstawiania z std::cout i m


	// The same as the call
	operator << ( std::cout, m );	// Wywołaj operator wstawiania z std::cout i m
}



#endif





