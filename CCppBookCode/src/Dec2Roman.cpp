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
#include <vector>
#include <string>
#include <tuple>
#include <algorithm>
#include <cassert>






using std::vector, std::string, std::tuple;
using std::cout, std::cin, std::endl;

// Konwertuje liczbę dziesiętną in_dec_num na tekst reprezentujący liczbę rzymską
auto ConvertDecimal_2_Roman( int in_dec_num )
{
	assert( in_dec_num <= 3999 );

	// Wartości muszą zostać posortowane od największej do najmniejszej
	const vector< tuple< int, string > > RomanValueTranslator  
    {
        {	1000,	"M"	},		{	900,	"CM"	},
        {	500,	"D"	},		{	400,	"CD"	},
        {	100,	"C"	},		{	90,		"XC"	},
        {	50,		"L"	},		{	40,		"XL"	},
        {	10,		"X"	},		{	9,		"IX"	},
        {	5,		"V"	},		{	4,		"IV"	},
        {	1,		"I"	}
    };

	string outStr { "" };
	// Przejdź po wszystkich krotkach [ val, str ], zaczynając od największej wartości val
	for( const auto & [ val, str ] : RomanValueTranslator )	// powiązanie strukturalne
        while( in_dec_num >= val )					// iteruj odejmując
            outStr += str, in_dec_num -= val;	// największą możliwą wartość

    return outStr;
}




void Dec_2_Roman_Test( void )
{
	cout << "1593 <=> " << ConvertDecimal_2_Roman( 1593 ) << endl;

	cout << "1968 <=> " << ConvertDecimal_2_Roman( 1968 ) << endl;
	
	cout << "1999 <=> " << ConvertDecimal_2_Roman( 1999 ) << endl;
	
	cout << "2008 <=> " << ConvertDecimal_2_Roman( 2008 ) << endl;
}


/////////////////////////////////////////////////////////////////////////


// Test jednostkowy dla funkcji ConvertDecimal_2_Roman
bool ConvertDecimal_2_Roman_UnitTest( void )
{
	assert( ConvertDecimal_2_Roman( 2000 ) == "MM" );
	assert( ConvertDecimal_2_Roman( 137 ) == "CXXXVII" );
	assert( ConvertDecimal_2_Roman( 1999 ) == "MCMXCIX" );
	//assert( ConvertDecimal_2_Roman( 2018 ) == "MMVIII" );	// pomyłka do wyłapania

	return true;
}




/////////////////////////////////////////////////////////////////////////



auto ConvertRoman_2_DecimalNumber( const string & Roman_str )
{
	int out_dec_num {};

	// Write the conversion algorithm ...


	return out_dec_num;
}




/////////////////////////////////////////////////////////////////////////




#include <random>

///////////////////////////////////////////////////////////
// Tworzy wektor z losowymi liczbami całkowitymi
///////////////////////////////////////////////////////////
//
// WEJŚCIE:
//			From, kTo – zakres wartości
//			kNumOfTrials - liczba wartości
// WYJDZIE:
//			vector< int > z losowymi wartościami w zakresie
//
auto	CreateRandomVector( const int kFrom, const int kTo, const int kNumOfTrials )					-> std::vector< int >
{
	// Do wygenerowania wartości losowych potrzebujemy:
	// (1) obiektu inicjalizacji losowości
    std::random_device rd;				
	// (2) silnika losowości 
	std::mt19937 mtRandomEngine( rd() );	// Mersenne twister MT19937? Czemu nie?
	// (3) biektu żądanego rozkładu
	std::uniform_int_distribution uni_distr( kFrom, kTo );		// wartości from_val-to_val

	std::vector< int >	random_decimals;	// będzie przechowywać losowe liczby całkowite

	// ygeneruj kNumOfTrials losowych wartości przez funkcję lambda łączącą 
	// uni_distr z mtRandomEngine. Używamy back_inserter, ponieważ wektor jest pusty.
	std::generate_n( back_inserter( random_decimals ), kNumOfTrials, [&](){ return uni_distr( mtRandomEngine ); } );
	
	return random_decimals;
}



///////////////////////////////////////////////////////////
// Test jednostkowy do losowego testowania obu konwersji
///////////////////////////////////////////////////////////
//
// WEJŚCIE:
//			kFrom, kTo - zakres wartości do przetestowania
//			kNumOfTrials - liczba losowych wartości testowych
// WYJŚCIE:
//			true, jeśli wszystkie testy zakończą się pomyślnie, false w przeciwnym razie
//
// UWAGI:
//			Wywołuje assert()
//
bool Decimal_2_Roman_Chain_UnitTest( const int kFrom = 1, const int kTo = 3999, const int kNumOfTrials = 1000 )
{
	// Sprawdź czy każda losowa liczba dziesiętna konwertuje się poprawnie
	for( const auto & val : CreateRandomVector( kFrom, kTo, kNumOfTrials ) )
		if(	ConvertRoman_2_DecimalNumber( ConvertDecimal_2_Roman( val ) ) != val )
			return false;  // test nie powiódł się, kończenie...

	return true;	// skoro tu dotarliśmy, wszystkie test zakończyły się sukcesem ;)
}




// Idea based on http://rosettacode.org/wiki/Roman_numerals/Encode#C.2B.2B



