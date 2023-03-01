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


// Nagłówki systemowe w < >
#include <ctime>


// ---------------------------------------
// Prosty pomocniczy generator liczb losowych

// Losowe liczby Xorshift Marsaglia
struct MarsXorShift
{
	// Wartość początkowa – musi być różna od  0
	unsigned long r_a_n_d { (unsigned long) time( nullptr ) & 0xFF };

	// Te wartości zostały znalezione przez G. Marsaglia
	// do generowania dosyć dobrze losowych wartości
	unsigned long GetNext( void )
	{
		r_a_n_d ^= r_a_n_d << 13;	// << to bitowe przesunięcie w lewo
		r_a_n_d ^= r_a_n_d >> 17;	// ^= to XOR i przypisz 
		r_a_n_d ^= r_a_n_d << 5;

		return r_a_n_d;
	}
};



