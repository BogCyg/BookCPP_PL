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
#include <string>
#include <functional>
#include <algorithm>
#include <limits>
#include <tuple>
#include <cassert>






namespace NewtonZero
{
	using FP = double;
	using Real_Fun = std::function< FP( FP ) >;

	// Pochodna również jest jednowymiarową funkcją rzeczywistą
	auto deriv( const Real_Fun & fun, const FP x0, const FP eps = 1e-5 )
	{
		// LUżyjmy definicji pochodnej
		return ( fun( x0 + eps ) - fun( x0 ) ) / eps;
	}


	///////////////////////////////////////////////////////////
	// Znajduje miejsca zerowe podanej funkcji
	///////////////////////////////////////////////////////////
	//
	// WEJŚCIE: 		fun ‐ obiekt funkcyjny
	//			start_x - oszacowany punk początkowy
	//			thresh - próg zbieżności
	// WYJŚCIE:
	//			krotka zawierająca parę wartości:
	//			- pozycja znalezionego zera
	//			- true, w przypadku osiągnięcia zbieżności obliczeń
	//
	// UWAGI:
	//			Tylko w przypadku zwrócenia true rezultat może być poprawny
	//
	auto FindZero( const Real_Fun & fun, const FP start_x, const FP thresh = 1e-10 )
	{
		FP x_n { start_x };

		const FP eps = std::numeric_limits< FP >::epsilon();

		// Tylko w przypadku true obliczenia mogą być poprawne
		bool reach_converg { false };

		// Zawsze dobrze jest mieć bezpiecznik na wypadek braku zbieżności obliczeń
		const size_t kMaxIters { 1000 };

		for( size_t n = 0; n < kMaxIters; ++ n )
		{
			// Ustaw próg
			const FP loc_thresh = std::max( thresh, eps * std::fabs( x_n ) );

			FP df_x = deriv( fun, x_n );

			// Sprawdź, czy możemy bezpiecznie dzielić
			if( std::fabs( df_x ) <= eps )
				break;

			// To jest krok Newtona
			FP delta = - fun( x_n ) / df_x;

			// Sprawdź pod kątem zbieżności
			if( std::fabs( delta ) <= loc_thresh )
			{
				reach_converg = true;		// Wynik może być OK
				break;		
			}

			x_n += delta;	// Zaktualizuj argument o deltę i iteruj
		}

		// Zwróć wynik – prawidłowy tylko, gdy reach_converg == true
		return std::make_tuple( x_n, reach_converg );
	}


}	// End of NewtonZero




// Some test functions
namespace NewtonZero
{

	void NewtonZero_Test( void )
	{	
		auto [ val, flag ] = FindZero(	[] ( double x ) { return x * x + x - 6.0; }, -1.5 );
	
		std::cout << "Zero at " << ( flag ? std::to_string( val ) : "none" ) << std::endl;
	}

}


namespace NewtonZero
{

	// Oblicz pierwiastek kwadratowy argumentu
	auto SquareRootApproxNewton( const FP arg )
	{
		// To jest funkcja odwrotna pierwiastka
		auto sq_root = [ arg = arg ] ( double x ) { return x * x - arg; };
	
		return FindZero( sq_root, 1.0 );
	}


	void SquareRoot_Test( void )
	{
		std::cout << "Enter positive value to compute the square root "; 

		double arg {};
		std::cin >> arg;
		if ( arg < 0.0 ) return;

		auto [ val, flag ] = SquareRootApproxNewton( arg );
		
		if( flag )
			std::cout << "sqrt( " << arg << " )= " << val << std::endl;	
		else
			std::cout << "Cannot compute the square root" << std::endl;

	}

}	// Koniec NewtonZero


