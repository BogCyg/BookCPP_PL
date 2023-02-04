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

#include "QuadEq.h"


// do pisania cout,
// a nie std::cout.
using std::cout, std::cerr, std::cin, std::endl;



// W C++ istnieją przeciążone funkcje main
int main()
{
	// Tekst odpowiadający wartościom TQuadEq::EEquationType 
	const std::string eq_types_text[] = {	"No real roots", 
											"One real root", 
											"Two real roots",
											"Linear equation, one root",
											"A contradictory equation"
										};


	cout << "Enter coefficients of the quadratic equation: a*x*x + b*x + c" << endl;
	double a = 0.0, b = 0.0, c = 0.0;
	cin >> a >> b >> c;

	TQuadEq		eq( a, b, c );		// Utwórz zainicjalizowany obiekt

	// Dla pierwiastków
	double x1 {}, x2 {};			// {} do zainicjalizowania x1 i x2 wartością zero

	TQuadEq::EEqType	eq_type {};

	try
	{
		eq_type = eq.GetRoots( x1, x2 );	// Tu może nastąpić zgłoszenie wyjątku
	}
	catch( const std::exception & e )
	{
		cerr << e.what() << endl;	// Jeśli tutaj, to błąd, więc wypisz powód
		return -1;	// Zakończ z kodem błędu
	}


	// Wszystko w porządku, więc wypisz rezultaty
	cout << eq_types_text[ static_cast< int >( eq_type ) ];
	
	// odatkowo, jeśli istnieją pierwiastki, wypisz je
	switch( eq_type )
	{
		case TQuadEq::EEqType::kOne:
		case TQuadEq::EEqType::kLinOne:
			cout << ": " << x1 << endl;
			break;

		case TQuadEq::EEqType::kTwo:
			cout << ": " << x1 << ", " << x2 << endl;
			break;

		default :
			break;
	}

	return 0;	// Zakończ z kodem OK
}
