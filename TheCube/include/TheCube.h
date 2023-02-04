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
#include <fstream>
#include <array>
#include <cassert>




using std::cout, std::cin, std::endl;	// Aliasy nazw




class TheCube
{
public:

	using value_type	= double;
	using size_type		= std::size_t;

	static const size_type kDims { 3 };		// to samo dla wszystkich obiektów klasy

	enum EDims { kx, ky, kz };				// skróty dla 3 wymiarów

private:

	// 'inteligentny' wskaźnik do 1-wymiarowego bufora ze wszystkimi danymi
	std::unique_ptr< value_type [] >	fDataBuf;

	// Tablica 3 wymiarów
	std::array< size_type, kDims >		fDim;

public:


	// Konstruktor domyślny
	TheCube( void )			// pusty bufor
		:	fDataBuf( nullptr ), fDim { 0, 0, 0 }	
	{
	}

	// Konstruktor parametryczny
	TheCube( const size_type dx, const size_type dy, const size_type dz )
		: fDim{ dx, dy, dz }
	{
		// Przydziel 1-wymiarową tablicę elementów value_type i przypisz do fDataBuf
		fDataBuf = std::make_unique< value_type [] >( fDim[ kx ] * fDim[ ky ] * fDim[ kz ] );
	}


	// Konstruktor kopiujący
	TheCube( const TheCube & cube )
	{
		fDim = cube.fDim;				// Najpierw skopiuj wymiary

		const auto	elems = fDim[ kx ] * fDim[ ky ] * fDim[ kz ];

		// Cokolwiek było w fDataBuf zostanie najpierw usunięte.
		// Następnie zostanie zaalokowany nowy bufor i dołączony do fDataBuf
		fDataBuf = std::make_unique< value_type [] >( elems );

		// Na koniec "głęboko" skopiuj dane do "tego" bufora
		//               cel                źródło                 bajty
		std::memcpy( fDataBuf.get(), cube.fDataBuf.get(), elems * sizeof( value_type ) );	
	}

	// Operator przypisania
	TheCube & operator = ( const TheCube & cube )
	{
		// Nie możemy skopiować, jeśli to ten sam obiekt
		if( this != & cube )
		{
			fDim = cube.fDim;					// Najpierw skopiuj wymiary

			const auto	elems = fDim[ kx ] * fDim[ ky ] * fDim[ kz ];

			// Cokolwiek było w fDataBuf zostanie najpierw usunięte
			// Nowy blok zostanie przydzielony i przypisany do fDataBuf
			fDataBuf = std::make_unique< value_type [] >( elems );

			// Na koniec wykonaj głęboką kopię danych do "tego" bufora		
			//           cel               źródło                bajty
			memcpy( fDataBuf.get(), cube.fDataBuf.get(), elems * sizeof( value_type ) );	
		}
		return * this;
	}


	// Destruktor – w przypadku planów dziedziczenia uczyń go wirtualnym
	~TheCube() {}


	// Konstruktor przenoszący (C++11)
	TheCube( TheCube && cube ) noexcept
		: fDataBuf( nullptr ), fDim { 0, 0, 0 }
	{
		// Zamień (wymiana) wymiary
		std::swap( fDim, cube.fDim );

		// Zamień przechowywane wskaźniki
		fDataBuf.swap( cube.fDataBuf );
	}



	// Operator przypisania przenoszący (C++11)
	TheCube & operator = ( TheCube && cube ) noexcept
	{
		// Zamień wszystkie dane składowe między this i cube
		std::swap( fDim, cube.fDim );

		// Tylko zamień wskaźniki – nie kopiuj buforów!
		fDataBuf.swap( cube.fDataBuf );		

		return * this;
	}



public:

	// Gettery/settery

	// Ponieważ EDims jako parametr, nie możemy prosić o nieistniejące wymiary
	auto	GetDim( EDims which_one ) const { return fDim[ which_one ]; }

	// Uzyskaj dostęp do elementów przez referencję - dwukierunkowo
	auto & Element( const int x, const int y, const int z ) const
	{ 
		const auto offset = ( z * fDim[ ky ] + y ) * fDim[ kx ] + x;
		return * ( fDataBuf.get() + offset ); 
	}

	auto	Size( void ) const { return fDim[ kx ] * fDim[ ky ] * fDim[ kz ]; }

	// Jest to funkcja const, ale pozwala na zmianę danych
	auto	GetDataBuf( void ) const { return fDataBuf.get(); }

public:

	// Operatory strumieniowania są funkcjami zewnętrznymi dla tej klasy
	friend std::ostream & operator << ( std::ostream & o,	const	TheCube & cube );
	friend std::istream & operator >> ( std::istream & i,	TheCube & cube );

};


