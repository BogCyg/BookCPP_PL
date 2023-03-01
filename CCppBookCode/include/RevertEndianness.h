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



#include <iostream>
#include <type_traits>		// dla is_unsigned_v



///////////////////////////////////////////////////////////
// Funkcja szablonowa do zmiany kolejności bajtów dla typów całkowitych
// tj. odwraca kolejność bajtów w argumencie wejściowym.
// Przykład: 0x78ABCDEF zostanie zmienione na 0xEFCDAB78
///////////////////////////////////////////////////////////
//
// INPUT:
//			in - integer like type
// OUTPUT:
//			byte reversed version of in
//
// REMARKS:
//
//
template < typename T >
constexpr auto RevertEndianness( T in ) 
{
	//static_assert( std::is_unsigned< T >::value );
	static_assert( std::is_unsigned_v< T > );

	T out { 0 };
	for( auto i { 0 }; i < sizeof( in ); ++ i )		// odwróć bajty
	{
		out <<= 8;
		out |= in & 0xFF;
		in >>= 8;
	}
	return out;
}



inline void RevertEndianness_Test( void )
{
	// RevertEndianness może zostać obliczona w czasie kompilacji
	// Zwróć uwagę na 'u' w 0xABCDu – dzięki temu 0xABCD jest stałą bez znaku
	std::cout << std::hex << std::uppercase << "ABCD" << "\t <-> "  
							<< RevertEndianness( 0xABCDu ) << std::endl;

	// W czasie kompilacji, ponieważ argument jest constexpr
	constexpr unsigned int ui { 0xABCDu };
	std::cout << std::hex << std::uppercase << ui << "\t <-> " 
							<< RevertEndianness( ui ) << std::endl;

	long l { 0x01234567 };
	// To się nie skompiluje, ponieważ l nie jest typu 'unsigned'
	//std::cout << std::hex << l << "\t <-> " 
	//						<< RevertEndianness( l ) << std::endl;

	unsigned long ul { 0x01234567ul };
	std::cout << std::hex << std::uppercase << ul << "\t <-> " 
							<< RevertEndianness( ul ) << std::endl;

	unsigned long long ull { 0x0123456789ABCDEFull };
	std::cout << std::hex << std::uppercase << ull << "\t <-> " 
							<< RevertEndianness( ull ) << std::endl;
}








