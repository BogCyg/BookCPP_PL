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
#include <iomanip>
#include <sstream>
#include <omp.h>		// Nagłówek dla OpenMP



#include "EMUtility.h"
#include "MarsXorShift.h"




// ------------------------------------------------------------------------
// Parallel versions






void OpenMP_Test( void )
{
	// To jest obiekt współdzielony ‐ ten sam dla wszystkich wątków.
	// Może wystąpić problem, gdy wiele wątków będzie chciało 
	// apisywać do niego JEDNOCZEŚNIE.
	std::ostringstream outStream;

	// Zaczynamy od kodu szeregowego wykonywanego przez jeden wątek linia po linii
	outStream << "Beginning with " << omp_get_num_threads() << " thread(s).\n";
	outStream << "Let's enter the omp parallel ...\n";

	// Przed sekcją równoległą ustaw liczbę 
	// wątków w zespole (nie mylić z rdzeniami) 
	//omp_set_num_threads( 36 );	

	// ------------------------
	// ‐‐‐ To jest RÓWNOLEGŁE ‐‐‐
	// Zobaczmy ZESPÓŁ wątków w akcji
	// However, declaring an object as shared
	// does NOT automatically makes its access
	// thread safe.
	#pragma omp parallel shared( outStream )
	{
		// To jest zmienna lokalna. Każdy wątek ma
		// swoją własną kopię tej zmiennej.
		auto thisThreadNo = omp_get_thread_num();

		// To również jest obiekt lokalny.
		const auto kNumOfThreads = omp_get_num_threads();

		// Użyjmy ‘critical’, aby zezwolić na działanie
		// tylko jednego wątku jednocześnie – w innym wypadku
		// będzie bałagan na ekranie.
		// NIE zapomnijmy tutaj o słowie kluczowym ‘omp’
		#pragma omp critical ( critical_0 )
		{
			outStream << "I'm thread no. " << thisThreadNo << " / " << kNumOfThreads << "\n";
		}

	}
	// Tu znajduje się BARIERA SYNCHRONIZACJI ‐ po niej wszystkie wątki zakończyły już prace
	// i wykonuje się tylko wątek główny
	// --- Koniec wykonywania RÓWNOLEGŁEGO ‐‐‐
	// ------------------------

	// Ponownie jeden wątek (główny), brak konieczności synchronizacji.
	outStream << "After crossing the parallel BARRIER we run " << omp_get_num_threads() << " thread(s).\n";

	// Zobaczmy, co zostało zebrane
	std::cout << outStream.str() << std::endl;

}



// Oblicza liczbę pi poprzez sumowanie szeregu arctan(1).
// N ‐ liczba wyrazów w szeregu.
double Compute_Pi( int N )
{
	const double dx = 1.0 / static_cast< double >( N );

	// To jest WSPÓŁDZIELONA zmienna
	double sum {};

	// -------------------------------------
	#pragma omp parallel for reduction( + : sum )	if( N > 1000000 )
	for( auto i = 0; i < N; ++ i )
	{
		auto c_i = dx * ( static_cast< double >( i ) + 0.5 );	// Zmienna lokalna
		
		// sum jest współdzielona, ale wyłączny dostęp gwarantowany jest przez reduction
		sum += 1.0 / ( 1.0 + c_i * c_i );	
	}
	// -------------------------------------

	return 4.0 * dx * sum;
}



void OpenMP_Pi_Test( void )
{

	auto N_list = { 100, 1000, 10000, 100000000 };

	for( const auto N : N_list )
	{
		// Zwraca liczbę sekund od czasu uruchomienia systemu operacyjnego.
		auto start_time = omp_get_wtime();	// Pozyskaj czas rozpoczęcia
			auto pi = Compute_Pi( N );		// Wykonaj obliczenia
		auto exec_time = omp_get_wtime() - start_time;	// Czas zakończenia

		std::cout	<< "pi(" << N << ")=" << std::setprecision( 12 ) 
					<< pi << " in " << exec_time << std::endl;
	}

}






// Overloaded operators 

// It can be used as follows: c = a + b;
EMatrix		operator + ( const EMatrix & a, const EMatrix & b )
{
	const auto a_cols = a.GetCols();
	const auto a_rows = a.GetRows();

	const auto b_cols = b.GetCols();
	const auto b_rows = b.GetRows();	

	assert( a_rows == b_rows );	// dim must be the same
	assert( a_cols == b_cols );

	EMatrix	c { a };	// Make c the same as a

						// Split the outermost for loop and run each chunk in a separate thread
#pragma omp parallel for \
		shared( b, c, b_rows, b_cols ) \
		default( none ) \
		schedule( static )

	for( Dim row = 0; row < b_rows; ++ row )
		for( Dim col = 0; col < b_cols; ++ col )
			c[ row ][ col ] += b[ row ][ col ];

	return c;
}

// Można go używać następująco: c = a * b;
EMatrix		operator * ( const EMatrix & a, const EMatrix & b )
{
	const auto a_cols = a.GetCols();
	const auto a_rows = a.GetRows();

	const auto b_cols = b.GetCols();
	const auto b_rows = b.GetRows();	

	assert( a_cols == b_rows );			// Wymiary muszą być takie same

	EMatrix	c( a_rows, b_cols, 0.0 );	// Macierz wynikowa ma te wymiary

	// Podziel najbardziej zewnętrzną pętlę for i wykonaj każdy fragment w osobnym wątku
	#pragma omp parallel for \
			shared( a, b, c, a_rows, b_cols, a_cols ) \
			default( none ) \
			schedule( static )
	// Tylko najbardziej zewnętrzna pętla będzie wykonywana równolegle
	for( Dim ar = 0; ar < a_rows; ++ ar )	// Przejdź po wierszach a
		for( Dim bc = 0; bc < b_cols; ++ bc )	// Przejdź po kolumnach b
			for( Dim ac = 0; ac < a_cols; ++ ac ) // Przejdź po kolumnach a == wierszach b
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




void OpenMP_MultMatrix_Test( void )
{
	const auto kCols { 1024 }, kRows { 1024 };
	EMatrix		a( kCols, kRows ), b( kRows, kCols );

	RandInit( a );
	RandInit( b );

	auto start_time = omp_get_wtime();	// Pozyskaj punkt początkowy

	EMatrix		c( a * b );				

	auto exec_time = omp_get_wtime() - start_time;	// Pomiar czasu końcowego


	std::cout << "Middle elem val: " << c[ kCols / 2 ][ kCols / 2 ] << std::endl;
	std::cout << "Computation time: " << exec_time << std::endl;
}


void OpenMP_MultMatrix_Test_1( void )
{
	const auto N = { 1024, 2048, 4096 };

	std::cout << "Matrix multiplication test ..." << std::endl;

	for( const auto dim : N )
	{


		EMatrix		a( dim, dim ), b( dim, dim );

		RandInit( a );
		RandInit( b );

		auto start_time = omp_get_wtime();	// Get time start point

		EMatrix		c( a * b );				

		auto exec_time = omp_get_wtime() - start_time;	// End time measurement


		std::cout << "Elems: " << dim << std::endl;
		std::cout << "Middle elem val: " << c[ dim / 2 ][ dim / 2 ] << std::endl;
		std::cout << "Computation time: " << exec_time << std::endl << std::endl;

	}

}



// ------------------------------------
// An example of hazards due to 
// an unprotected shared object

int x;		// A global shared variable

void Task_0( void )
{
	auto loc { x };	// Local object
	
	// Non-protected access to shared
	x += 5;
	
	std::cout << loc << ", " << x << "\n";
}

void Task_1( void )
{
	#pragma omp critical ( section )
	{
		auto loc { x };	// Copy whatever value of x

		x += 5;	// ok

		std::cout << loc << ", " << x << "\n";
	}
}

void Parallel_Tasks_Test( void )
{
	// There is nothing wrong with Task_0 
	// when executed sequentially.
	for( auto i : { 1, 2, 3, 4, 5 } )
		Task_0();

	std::cout << "\n\n";

	// Run unprotected
	#pragma omp parallel num_threads( 5 )
	{		
		Task_0();
	}

	// Run with critical section
	#pragma omp parallel num_threads( 5 )
	{
		Task_1();
	}

}






