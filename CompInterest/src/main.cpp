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


#include <cmath>
#include <iostream>



// Wprowadź nazwy obiektów wejścia i wyjścia z przestrzeni nazw std
using std::cout, std::cin, std::endl;


// Ten program oblicza procent składany
// 
int main()
{

	// ----------------------------------------------------
	cout << "Wprowadź początkową kwotę jaką chcesz zainwestować: " << endl;
	double C_0 {};
	cin >> C_0;


	if( C_0 <= 0.0 )
	{
		cout << "Nieprawidłowa wartość, kończę działanie..." << endl;
		return -1;
	}

	// -------------------------------------------
	cout << "Wprowadź roczne oprocentowanie [% na 12 miesięcy]: " << endl;
	double r {};
	cin >> r;
	if( r <= 0.0 || r >= 100.0 )
	{
		cout << "Nieprawidłowa wartość, kończę działanie..." << endl;
		return -1;
	}

	// -------------------------------------------
	cout << "Okres kapitalizacji to wyrażony w miesiącach czas pomiędzy naliczeniami odsetek" << endl;
	cout << "(np. jeśli naliczenie ma miejsce 2 razy do roku, wprowadź 6)" << endl;
	cout << "Jeśli nie wiesz, wprowadź 12 dla rocznego okresu kapitalizacji." << endl;
	cout << "Wprowadź okres kapitalizacji [w miesiącach, od 1 do 72]: " << endl;
	double t {};
	cin >> t;
	if( t <= 0.0 || t > 72.0 )
	{
		cout << "Nieprawidłowa wartość, kończę działanie..." << endl;
		return -1;
	}
	// ---------------------------------------------------
	cout << "Wprowadź czas inwestycji [w miesiącach, od 1 do 100]: " << endl;
	double m {};
	cin >> m;
	if( m <= 0.0 || m >= 100 )
	{
		cout << "Nieprawidłowa wartość, kończę działanie..." << endl;
		return -1;
	}

	// ------------------------------
	// Wykonaj obliczenia

	const double kMontsPerYear	= 12.0;
	const double kPercentageDiv = 100.0;

	double i = m / t;		// Okresy kapitalizacji

	double C_i = C_0 * std::pow( ( 1.0 + ( r / kPercentageDiv ) / kMontsPerYear * t ), i );

	cout << "Twoje saldo przed opodatkowaniem po " << m;
	cout << " miesiącach inwestycji wynosi: " << C_i << endl;

	// Oblicz dochód netto
	double income = C_i - C_0;
	cout << "Twój dochód wynosi " << income << endl;
	const double kIncomeTax = 19.0;		// 19%
	cout << "Po potrąceniu " << kIncomeTax << "% podatku dochód wynosi: ";
	cout << ( 1.0 - kIncomeTax / kPercentageDiv ) * income << endl;

	return 0;
}





