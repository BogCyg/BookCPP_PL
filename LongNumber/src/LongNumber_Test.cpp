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
#include "LongNumberFor.h"

using std::cout, std::endl;
using std::ofstream, std::ifstream;



// Funkcja, która sprawdza główną funkcjonalność
// klasy TLongNumberFor
void LongNumbers_Test( void )
{
	try
	{
		TLongNumberFor< 11 > pesel;

		pesel.SetNumberAt( 7, 7 );
		pesel.SetNumberAt( 8, 8 );

		assert( pesel.GetNumberAt( 7 ) == 7 );
		assert( pesel.GetNumberAt( 8 ) == 8 );


		// Spróbuj wykonać konwersję
		TLongNumberFor< 5 > number_1(  "1234" );

		std::string str { "--" };	// Utwórz std::string z number_1
		str += number_1;		// Skonwertuj number_1 na std::string i złącz z str
		std::cout << str << endl;	// Pokaż rezultat

		{

			ofstream testFile( "TLongNumberFor.txt" );
			testFile << number_1;
			testFile.close();
		}


		TLongNumberFor< 5 > number_2;
		{
			ifstream testFile( "TLongNumberFor.txt" );
			testFile >> number_2;
			testFile.close();
		}

		assert( number_1 == number_2 );

		// Teraz spróbujmy uzyskać dostęp na złej pozycji
		//cout << number_1[ 33 ];
	}
	catch( const std::exception & e )
	{
		std::cerr << "Out of Range error: " << e.what() << '\n';
	}
	catch( ... )
	{
		std::cerr << "Unknown exception\n";
	}
}








// Funkcja, która sprawdza główną funkcjonalność klasy
// TLongNumberFor, zawierającej wzorzec pełnomocnika
void LongNumbersWithProxy_Test( void )
{
#ifdef TURN_ON_PROXY

	TLongNumberFor< 11 > id;

	int x = id[ 7 ];	// użyj tutaj pełnomocnika

	id[ 7 ] = 7;		// użyj tutaj pełnomocnika

	id[ 6 ] = id[ 8 ] = id[ 7 ] = 3;	// tutaj również użyj pełnomocnika		

	assert( id[ 6 ] == 3 );
	assert( id[ 7 ] == 3 );
	assert( id[ 8 ] == 3 );

	assert( id[ 10 ] == id[ 0 ] );

#endif

	// Zgodne indeksowanie: 9 ... 0
	const TLongNumberFor< 11 > cid( "9876543210" );	// cid zawiera "09876543210"
	assert( cid[ 10 ] == cid[ 0 ] );	// wiodąca 11-ta cyfra została ustawiona na 0

	//cid[ 0 ] = 5;		nie można wykonać, ponieważ cid jest const
	int z = cid[ 7 ];	// wywołuje const int TLongNumberFor< 11 >::operator [] ( int position ) const

#ifdef TURN_ON_PROXY

	id[ 7 ] = cid[ 1 ];
	assert( id[ 7 ] == 1 );

#endif
}
