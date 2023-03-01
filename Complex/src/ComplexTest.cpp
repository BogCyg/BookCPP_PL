/// ==========================================================================
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





#include <fstream>

#include "Complex.h"




using std::cout, std::cin, std::endl;
using std::ofstream, std::ifstream;

using CppBook::TComplex;



// Proste operacje na liczbach zespolonych
// z użyciem klawiatury i ekranu
void Complex_Test_Screen( void )
{
	//////////////////////////////////////////
	// Utwórzmy kilka obiektów TComplex:
	CppBook::TComplex	a, b,			// a i b za pomocą konstruktora domyślnego
						c( 10., 20. );	// c za pomocą konstruktora parametrycznego

	TComplex d( c );	// Kolejny, tym razem d zawiera kopię obiektu c

	// Przetestujmy strumieniowanie obiektu d na ekran
	cout << d << endl;		
	operator << ( cout, d );	// Możemy również napisać to tak,
	cout << endl;				// a następnie przejść do nowej linii

	cout << "Write re, press Enter, then im, press Enter" << endl;
	cin >> a;	// Wczytaj z klawiatury nowe wartości dla obiekty a

	c = b = a;	// Skopiuj a do b, następnie b do c (= ma łączność prawostronną)

	// Dodajmy do siebie dwie liczby zespolone b i d, i wypiszmy rezultat
	cout << "( " << a << " ) + ( " << b << " ) = ( " << a + b << " ) " << endl;	

	// Aby przypisać 5.0 do b, 5.0 musi zostać skonwertowane na TComplex, a potem przypisane.
	b = 5.0;
	cout << "( " << a << " ) + ( " << b << " ) = ( " << a + b << " ) " << endl;	
}


// Proste operacje na liczbach zespolonych
// z użyciem klawiatury, ekranu i pliku
void Complex_Test_File( void )
{
	// Utwórz dwa obiekty zespolone
	TComplex	a, b;			
		
	// Wprowadź je z klawiatury
	cout << "Enter 1st complex" << endl;
	cin >> a;

	cout << "Enter 2nd complex" << endl;
	cin >> b;

	// Spróbujmy skopiować wyniki do pliku otwartego w trybie dopisywania
	ofstream theFile( "ComplexTest.txt", std::ios::app );	 

	// Zawsze sprawdzaj, czy plik został prawidłowo otwarty
	if( theFile.is_open() == true )
	{
		// Wykonaj operacje i wypisz wyniki do pliku
		theFile << "a = " << a << ", b = " << b << endl;
		theFile << "a + b = " << a + b << endl;
		theFile << "a - b = " << a - b << endl;
		theFile << "a * b = " << a * b << endl;

		// Dzielenie jest jednak inne – może zgłosić wyjątek
		try
		{
			// Trzymaj to w bloku try-catch
			theFile << "a / b = " << a / b << endl << endl;
		}
		catch( std::exception & e )		// przechwyć wyjątki
		{
			// Standardowe wyjątki będą przetwarzane tutaj
			std::cerr << "Exception caught: "	<< e.what() << endl;	// wypisz przyczynę
		}
		catch( ... ) 
		{
			// Dowolny inny wyjątek zostanie przechwycony tutaj
			std::cerr << "Unknown error" << endl;	
		}		

	}

}

