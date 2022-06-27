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
#include "FxFor.h"




// -----------------------------

// Nowy sposób definiowania stałych
// za pomocą szablonów zmiennych
template< typename T >
constexpr T gkPi = T( 3.1415926535897932385 );


// Pomocniczy wieloliniowy symbol końca linii
template < auto REP = 1, auto CHAR = '\n' >
std::ostream & endl( std::ostream & o )
{
	// Unikaj wysyłania endl ‐ opróżnia on strumień
	return o << std::string( REP, CHAR );
}

// -----------------------------


using std::cout/*, std::endl*/;



void FxPt_Test_1( void )
{
	constexpr auto & kPi { gkPi< double > };


	constexpr FX_8_8	kPi_8_8( gkPi< FX_8_8 > );

	// Sprawdza, czy kPi_8_8 jest tworzona podczas kompilacji
	static_assert( kPi_8_8.GetInternalValue() >= 0 );

	// double
	constexpr double	radius( 2.0 );
	constexpr auto area_d ( kPi * radius * radius );

	// FX_8_8
	constexpr FX_8_8	radius_8_8( radius );
	constexpr FX_8_8	area_8_8( gkPi< FX_8_8 > * radius_8_8 * radius_8_8 );

	static_assert( area_8_8.GetInternalValue() >= 0 );



	static_assert( ComputeRoundingError( area_8_8, area_d ) < 0.005 );

	// area_d i area_8_8 zostały już wstępnie obliczone w czasie kompilacji
	cout << "sizeof(double) = " << sizeof( double );
	cout << ", area< double > = " << area_d << endl;
	cout << "sizeof(FX_8_8) = " << sizeof( FX_8_8 );
	cout << ", area< FX_8_8 > = " << static_cast< double >( area_8_8 ) << endl;
	cout << "Diff = " << ComputeRoundingError( area_8_8, area_d ) << endl << endl< 7 >;



	// ------------------------------------------
	// Oblicz w czasie działania

	auto cyl_len { 1000.0 };

	// Dojdzie do przepełnienia
	cout << "volume< FX_8_8 > = " << static_cast< double >( area_8_8 * FX_8_8( cyl_len ) ) << endl;


	FX_16_16	area_16_16( area_8_8 );		// zainicjalizuj szerszą przy użyciu krótszej



	// Oblicz objętość walca
	area_16_16 *= cyl_len;

	cout << "volume< FX_16_16 > = " << static_cast< double >( area_16_16 ) << endl;

}



void FxPt_Test_2( void )
{
	// ------------------------------------------
	// const kontra constexpr

	const FX_8_8		d1 {};	// d1 będzie stałą
	constexpr FX_8_8	d2 {};	// d2 będzie stałą i zostanie obliczona podczas kompilacji

	// Nie skompiluje się – nie jest wystarczająca, musi być constexpr
	// static_assert( d1.GetInternalValue() >= 0 );

	// To jest ok 
	static_assert( d2.GetInternalValue() >= 0 );	
	// Nie skompiluje się ‐ d2 jest stałą FX_8_8
	// d2 *= 2.0;
}



void FxPt_Test_3( void )
{

	using FX_char	= FxFor< unsigned char, 0  >;
	using FX_int	= FxFor< unsigned int,	0 >;

	FX_char		x1( -5 );

	FX_int		x2( 13 );


	FX_8_8		x3( 5.5125 );

	FX_16_16	x4( -13.625 );


	cout << (double)x1 << endl;
	cout << (double)(char)x1 << endl;
	cout << (double)(int)x1 << endl;

	cout << (double)x2 << endl;
	cout << (double)(char)x2 << endl;
	cout << (double)(int)x2 << endl;
	cout << (double)(long)x2 << endl;

	cout << (double)x3 << endl;
	cout << (double)(char)x3 << endl;
	cout << (double)(char)(x3 - FX_8_8(0.1) ) << endl;
	cout << (double)(x3 + x1) << endl;
	cout << (double)(x1 + x3) << endl;

	if( (x3 - FX_8_8(0.1) ) > x3 )
		cout << "(x3 - FX_8_8(0.1) ) > x3" << endl;
	if( (x3 - FX_8_8(0.1) ) < x3 )
		cout << "(x3 - FX_8_8(0.1) ) < x3" << endl;
	if( (x3 - FX_8_8(0.1) ) <= x3 )
		cout << "(x3 - FX_8_8(0.1) ) <= x3" << endl;
	if( (x3 - FX_8_8(0.1) ) != x3 )
		cout << "(x3 - FX_8_8(0.1) ) != x3" << endl;

	cout << (double)x4 << endl;
	cout << (double)(x4 + x2) << endl;
	cout << (double)(x2 + x4) << endl;


}





