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



#include <algorithm>
#include <random>

#include "TheCube.h"




TheCube	RetAbsCube( const TheCube & inCube );


// Funkcja testowa dla klasy TheCube
void TheCube_Test( void )
{
	const int dx { 15 }, dy { 13 }, dz { 11 };

	TheCube		cube( dx, dy, dz );

	// Algorytm losowości Mersenne twister
	std::mt19937		rand_gen{ std::random_device{}() }; 	

	// Wypełnij sześcian losowymi wartościami. ref jest otoką referencji
	std::generate( cube.GetDataBuf(), cube.GetDataBuf() + cube.Size(), std::ref( rand_gen ) );

	// Nie można przenieść – tylko kopia z cube, ponieważ jest ona używana później
	TheCube		mirror_cube( cube );	


	cube.Element( 5, 7, 9 ) = -100.0;		// Ustaw jako element,
	assert( cube.Element( 5, 7, 9 ) == -100.0 );		// odczytaj i sprawdź, czy takie same

	std::ofstream outFile( "TheCube.bin", std::ios::binary );
	outFile << cube;
	outFile.close();	// żeby można było otworzyć w kolejnej linii

	std::ifstream inFile( "TheCube.bin", std::ios::binary );
	TheCube		testCube;
	inFile >> testCube;


	// Sprawdź bajt po bajcie, czy dane są takie same
	assert( std::memcmp( cube.GetDataBuf(), testCube.GetDataBuf(), cube.Size() * sizeof( TheCube::value_type ) ) == 0 );


	// Wywołaj konstruktor przenoszący
	TheCube abs_cube( RetAbsCube( cube ) ); 

	// Wywołaj jawnie przenoszący operator przypisania
	cube = static_cast< TheCube && >( abs_cube );	


	std::ofstream outAbsFile( "TheAbsCube.bin", std::ios::binary );
	outAbsFile << cube;

}



TheCube	RetAbsCube( const TheCube & inCube )
{
	// Utwórz pustą kostkę o tych samych wymiarach co inCube
	TheCube outCube(	inCube.GetDim( TheCube::kx ), 
		inCube.GetDim( TheCube::ky ), 
		inCube.GetDim( TheCube::kz ) );		

	// Przekształć wszystkie elementy na ich bezwzględne wartości
	std::transform( inCube.GetDataBuf(), inCube.GetDataBuf() + inCube.Size(), 
		outCube.GetDataBuf(), [] ( TheCube::value_type v ) { return std::fabs( v ); } );
	return outCube;			// Wywołuje semantykę przenoszenia
}







