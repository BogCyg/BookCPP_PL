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



#include <vector>			// Nagłówek pozwalający użyć std::vector
#include <iostream>			// Nagłówki dla wejścia i wyjścia
#include <iomanip>			// oraz formatowania wyjścia
#include <cmath>			// Dla funkcji matematycznych


// Wprowadzamy poniższe, aby móc pisać vector zamiast std::vector
using std::cout, std::cin, std::endl, std::vector; 


int main()
{

	cout << "Enter your grades" << endl;

	vector< double >		studentGradeVec;	// Pusty wektor wartości double

	// Zbierz oceny studentów
	for( ;; )
	{
		double grade {};

		cin >> grade;

		// Jeśli ok, wstaw nową ocenę na końcu wektora
		if( grade >= 2.0 && grade <= 5.0 )
			studentGradeVec.push_back( grade );

	
		cout << "Enter more? [y/n] "; 
		char ans {};
		cin >> ans;

		if( ans == 'n' || ans == 'N' )
			break;		// sposób na wyjście z pętli
	}

	
	// Ok, jeśli są jakiekolwiek oceny, oblicz ich średnią
	if( studentGradeVec.size() > 0 )
	{
		double sum { 0.0 };
		// Zsumuj wszystkie oceny
		for( auto g : studentGradeVec )
			sum += g;

		double av = sum / studentGradeVec.size(); // Typ zostanie wypromowany do double

		double finalGrade {};

		// Niech się dostosuje
		if( av < 3.0 )
		{
			finalGrade = 2.0;
		}
		else
		{
			double near_int = std::floor( av );	// pozyskaj część całkowitą
			double frac		= av - near_int;	// pozyskaj samą część ułamkową

			double adjust { 0.5 };	// nowa wartość dostosowania

			if( frac < 0.25 )
				adjust = 0.0;
			else if( frac > 0.75 )
				adjust = 1.0;

			finalGrade = near_int + adjust;
		}

		cout	<< "Final grade: " 
				<< std::fixed << std::setw( 3 ) << std::setprecision( 1 ) 
				<< finalGrade << endl;

	}


	return 0;
}


