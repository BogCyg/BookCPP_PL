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
#include <vector>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <array>
#include <random>
#include <fstream>
#include <tuple>
#include <cassert>
#include <time.h>





///////////////////////////////////////////////////////////////////////////////////


#include <iostream>

using std::cout, std::cin, std::endl;


// Deklaracja funkcji – wprowadzamy nową funkcję.
// Jej pełna definicja znajduje się gdzie indziej.
double SumOfSquares( double a, double b );


void SumOfSquaresTest( void )
{
	double x { 0.0 }, y { 0.0 };	// dwie zmienne typu zmiennoprzecinkowego

	cout << "Enter two values" << endl;
	cout << "x = "; 
	cin >> x;
	cout << "y = ";
	cin >> y;

	// Zmienna sum będzie zawierać wartość zwróconą przez funkcję SumOfSquares
	double sum = SumOfSquares( x, y );

	cout << "x*x + y*y = " << sum << endl;
}


///////////////////////////////////////////////////////////
// Oblicza i zwraca sumę kwadratów jej argumentów
///////////////////////////////////////////////////////////
//
// WEJŚCIE:
//			a, b – wartości zmiennoprzecinkowe
// WYJŚCIE:
//			Suma kwadratów a i b, tj.: 
//			a * a + b * b
//
// UWAGI:
//			Parametry przekazywane przez wartość (kopie)
//
double SumOfSquares( double a, double b )
{
	return a * a + b * b;
}




///////////////////////////////////////////////////////////


// Zdefiniujmy zewnętrzną stałą Pi
const double kPi = 3.1415926535897932385; 

namespace Deg_2_Rad_Val
{

	// Konwertuje stopnie na radiany.
	// Przekaż "deg" przez kopię
	double Deg_2_Rad( const double deg )
	{
		// Cokolwiek dzieje się tutaj ze zmienną deg 
		// będzie miało na nią wpływ wyłącznie tutaj
		return kPi * deg / 180.0;
	}

}


namespace Deg_2_Rad_Ref
{


	// Ta sama akcja, ale dostęp pośredni 
	// z użyciem stałej referencji.
	// W C++ możemy używać tych samych nazw funkcji
	// pod warunkiem, że ich parametry będą inne (przeciążanie)
	double Deg_2_Rad( const double & deg )
	{
		// deg jest referencją do obiektu
		// zdefiniowanego poza funkcją Deg_2_Rad;
		// deg może być tylko odczytywana, ponieważ jest to stała referencja
		return kPi * deg / 180.0;	// taki sam wzór co wcześniej
	}


}

namespace Deg_2_Rad_IO_Ref
{
	// Konwertuje "val" ze stopni na radiany w miejscu
	// Działa, ale może zaskoczyć ...
	void Deg_2_Rad( double & val )
	{
		val *= kPi / 180.0;
	}

}


// Pośrednia wersja ze wskaźnikiem (jedyny możliwy sposób w języku C)
// deg musi być prawidłowym wskaźnikiem. 
void Deg_2_Rad( double * deg )
{
	// Powinniśmy sprawdzić, czy deg nie jest nullptr?
	assert( deg != nullptr );

	* deg = kPi * * deg / 180.0;

	deg = nullptr ;	// deg jest wskaźnikiem lokalnym – możemy go tu wyzerować
					// ale nic nie stanie się obiektowi zewnętrznemu
}




// Przykłady wywołań funkcji
void FunctionCallTest( void )
{
	{
		double d { 0.0 };		// przechowuje stopnie

		cout << "Enter degs: ";
		cin >> d;

		double r { 0.0 };		// tutaj będziemy przechowywać radiany

		r = Deg_2_Rad_Val::Deg_2_Rad( d );	// wywołaj Deg_2_Rad, zmienna d nie zostanie zmieniona

		cout << d << " degs = " << r << " rad" << endl;
	}

	// ----------------

	{
		double d { 0.0 };		// przechowuje stopnie

		cout << "Enter degs: ";
		cin >> d;

		double r { 0.0 };		// tutaj będziemy przechowywać radiany

		r = Deg_2_Rad_Ref::Deg_2_Rad( d );	// wywołaj Deg_2_Rad, zmienna d nie zostanie zmieniona

		cout << d << " degs = " << r << " rad" << endl;	
	
	}
	
	// ----------------

	{

		double d { 0.0 };		// przechowuje stopnie

		cout << "Enter degs: ";
		cin >> d;

		double d_storage = d;		// tutaj będziemy przechowywać stopnie na później

		Deg_2_Rad_IO_Ref::Deg_2_Rad( d );	// wywołaj Deg_2_Rad, zmienna d zostanie zmieniona (!)

		cout << d_storage << " degs = " << d << " rad" << endl;	

	}

	// ----------------

	{

		double d { 0.0 };		// przechowuje stopnie

		cout << "Enter degs: ";
		cin >> d;

		double d_storage = d;		// tutaj przechowamy radiany na później

		Deg_2_Rad( & d );	// wywołaj Deg_2_Rad, d zostanie zmieniona

		cout << d_storage << " degs = " << d << " rad" << endl;	

	}



}



//
//float FuelConsumption( float km, float fuel );
//
//
//float FuelConsumption( float km, float fuel )
//{
//	return fuel / km * 100.0;
//}







// New way of defining constants
// with variable templates
template< typename T >
constexpr T gkPi = T( 3.1415926535897932385 );


template < typename C >
const C GetCircleArea( const C radius )
{
	return gkPi< C > * radius * radius;
}



///////////////////////////////////////////////////////

// Zwraca n-ty element ciągu Fibonacciego.
// Funkcja rekurencyjna
int	FiboRecursive( const int n )
{
	assert( n < 100 );	// "bezpiecznik" chroniący przed przepełnieniem stosu

	if( n == 0 || n == 1 ) 
		return n;
	else
		return FiboRecursive( n - 1 ) + FiboRecursive( n - 2 );
}


void FiboRecursive_Test( void )
{
	cout << "Enter Fibonacci level: ";

	int fibo {};	// zdefiniuj i zainicjalizuj wartością 0
	cin >> fibo;	// odczytaj z klawiatury

	// wyświetl
	cout << "Fibonacci at level " << fibo << " is " << FiboRecursive( fibo ) << endl;
}

