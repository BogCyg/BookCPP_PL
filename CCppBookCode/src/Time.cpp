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



#include <string>
#include <iostream>

#include <chrono>
#include <ctime>
#include <cassert>
#include <functional>
#include <random>

#include "range.h"



using namespace std;
using CppBook::range;



// https://en.cppreference.com/w/cpp/chrono


// Returns a string with current date & time
string	GetCurrentTime( void )
{
	using timer = std::chrono::system_clock;
    std::time_t time_point = timer::to_time_t( timer::now() );
	return std::ctime( & time_point );
}


using fun_void_int = std::function< void( int ) >;


// Launches fun( fun_param ) and measures its time
void fun_perform_timer( fun_void_int fun, int fun_param )
{
	using timer = std::chrono::high_resolution_clock;

	// ----------------------------
    auto timer_start = timer::now();
    
	// run function here ...
	fun( fun_param );

    auto timer_end = timer::now();
 	// ----------------------------

    std::chrono::duration< double > comp_period = timer_end - timer_start;

	cout << "Computation time = " << comp_period.count() << " [s]" << endl;

	cout << "Computation time = " <<  std::chrono::duration_cast< std::chrono::seconds >( comp_period ).count() << " [is]" << endl;

	cout << "Computation time = " <<  std::chrono::duration_cast< std::chrono::microseconds >( comp_period ).count() << " [us]" << endl;
}


void arithm_fun( int p )
{
	for( auto a : range( p ) )
		cout << a * a << " ";
}

void fun_perform_timer_test( void )
{
	fun_perform_timer( arithm_fun, 23 );
}


// -------------------------------------------



namespace CppBook
{
	// Zagnieżdżona przestrzeń nazw
	namespace LTimer
	{
		/*const*/ int kIterations = 10;

		///////////////////////////////////////////////////////////
		// Lambda do pomiaru czasu wykonywania funkcji przyjmującej dowolny
		// zestaw parametrów.
		///////////////////////////////////////////////////////////
		//
		// WEJŚCIE:
		//			func - funkcja do wywołania jako: func( func_params )
		// WYJŚCIE:
		//			czas w milisekundach dla pojedynczego wykonania func
		//
		// UWAGI:
		//			func zostanie wywołana kIterations razy, a czas 
		//			wykonania zostanie uśredniony
		//
		auto measureFuncAvTiming = [ iter = kIterations ]( auto && func, auto && ... func_params )               
		{
			static_assert( kIterations > 0 );	// sprawdź w czasie kompilacji

			using timer = typename std::chrono::high_resolution_clock;
			
			auto time_start = timer::now();
				  
				// Wykonaj algorytm pewną liczbę iteracji
				for( auto i : range( iter ) )
					std::forward< decltype( func ) >( func )
					( 
						std::forward< decltype( func_params ) >( func_params ) ... 
					);

			// COblicz średni czas wykonywania func w milisekundach
			return 	std::chrono::duration_cast< std::chrono::milliseconds >
						( timer::now() - time_start ).count() 
						/ /*kIterations*/iter;
		};

	}

}


void MathFun( int iters, double weight )
{
	for( int i = 0; i < iters; ++ i )
		cout << sqrt( i * weight ) << endl;
}

void TestSimpleFunctionTimeMeasurement( void )
{
	auto funTimer { CppBook::LTimer::measureFuncAvTiming };

	auto run_time = funTimer( MathFun, 234, 0.13 );

	cout << "MathFun run-time: " << run_time << " [ms]" << endl;
}


void MathFun_RandTest( int iters, double eps, double & result )
{
	// Zainicjuj Mersenne twister
	std::mt19937 mtRandomEngine( (random_device())() );	
	std::bernoulli_distribution bern( 0.7 ); // 0 lub 1 z p=0.7

	result = 0.0;
	for( int i = 0; i < iters; ++ i )
		result += bern( mtRandomEngine );

	result /= static_cast< double >( iters ) + eps;
}

void TestFunctionTimeMeasurement( void )
{
	auto funTimer { CppBook::LTimer::measureFuncAvTiming };

	double result {};

	auto run_time = funTimer( MathFun_RandTest, 1234567, 1e-5, result );

	cout << "MathFun_RandTest last result: " << result << endl;
	cout << "MathFun_RandTest run-time: " << run_time << " [ms]" << endl;
}




// -------------------------------------------


void EratosthenesSieve_TimeTest( void )
{
	vector< int > EratosthenesSieve( const int val );
	cout	<< "EratosthenesSieve run-time: " 
			<< CppBook::LTimer::measureFuncAvTiming( EratosthenesSieve, 2000000 ) 
			<< " [ms]" << endl;
}


// -------------------------------------------
