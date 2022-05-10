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
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>



// Wylistowanie ich w tym miejscu pozwala pominąć std::
using std::cout, std::cin, std::endl;
using std::string, std::vector;





void  letter_histogram( void )
{
	// Utwórz slot dla każdej litery, od ’a’ to ’z’. 
	// Początkowo dla każdej z nich ustaw licznik na 0. 
	std::vector histogram( 'z' - 'a' + 1, 0 );

	std::string in_str;

	//std::cin >> in_str;
	in_str = "AGH University of Science and Technology";

	for( auto c : in_str )
		if( isalpha( c ) )
			++ histogram[ tolower( c ) - 'a' ];

	cout << endl;  

	for( auto k { 'a' }; k <= 'z'; ++ k )
		cout << k << " ";		// Wypisz wszystkie znaki od ’a’ do ’z’

	cout << endl;  

	for( auto h : histogram )
		cout << h << " ";		// Wypisz wartości histogramu

	cout << endl;  
}




// 2nd version using the ST algorithms
void letter_histogram_stl( void )
{
	std::vector histogram( 'z' - 'a' + 1, 0 );

	std::string in_str;

	//std::cin >> in_str;
	in_str = "AGH University of Science and Technology";


	std::for_each(	in_str.begin(), in_str.end(), 
		[ & histogram ] ( const auto c )	{ 
		if( isalpha( c ) ) 
			++ histogram[ tolower( c ) - 'a' ];
	} 
	);


	cout << endl;  
	std::generate_n( std::ostream_iterator< char >( std::cout, " " ), histogram.size(), [ k = 'a' ] () mutable { return k ++; } );

	cout << endl;  
	std::copy( histogram.begin(), histogram.end(), std::ostream_iterator< int >( std::cout, " " ) );

	cout << endl;  

}





