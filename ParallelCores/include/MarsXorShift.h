// ==========================================================================
//
// Oprogramowanie napisane przez prof. Bogus³awa Cyganka do u¿ytku z ksi¹¿k¹:
// ==> Programowanie w jêzyku C++. Wprowadzenie dla in¿ynierów. PWN 2023 <==
//
// Oprogramowanie jest dostarczane w stanie takim, w jakim jest, i do celów edukacyjnych
// bez ¿adnych gwarancji ani odpowiedzialnoœci za jego u¿ycie w jakiejkolwiek aplikacji.
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
#include <time.h>


// ------------------------------------
// A helper simple random generator

// Marsaglia's Xorshift random numbers
struct MarsXorShift
{
	// Start value - must be different from 0
	unsigned long r_a_n_d { (unsigned long) time( nullptr ) & 0xFF };

	// These values were found by G. Marsaglia
	// to generate quite good random values
	unsigned long GetNext( void )
	{
		r_a_n_d ^= r_a_n_d << 13;	// << is bit left shift
		r_a_n_d ^= r_a_n_d >> 17;	// ^= is XOR 
		r_a_n_d ^= r_a_n_d << 5;

		return r_a_n_d;
	}
};



