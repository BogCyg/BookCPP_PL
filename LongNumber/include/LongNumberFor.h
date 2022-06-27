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



#include <cassert>
#include <string>
#include <array>
#include <iostream>
#include <algorithm>
#include <exception>


using std::string;
using std::istream, std::ostream;


// ===============================================================================



// Ta klasa przechowuje w wydajny sposób serię liczb, takich jak 12345678901234567890,
// odanej długości. Każda liczba przechowywana jest w półbajcie (tj. na czterech bitach).
//
// Słowo kluczowe auto w parametrze szablonu -
// typ dedukowany jest w czasie tworzenia instancji. 
//
template < auto MAX_NUMBERS >
class TLongNumberFor
{
	public:

		//enum { kMaxNumbers = MAX_NUMBERS };
		inline static const auto kMaxNumbers { MAX_NUMBERS };

	private:

		// --------------------------------
		// Klasa może definiować kolejna klasę
		// Ta klasa definiuje 2 cyfry do przechowania
		struct NibblePair
		{
				unsigned char fFirst	: 4;		// zdefiniuj dwa pola bitowe
				unsigned char fSecond	: 4;		// o całkowitym rozmiarze 1 bajtu

				NibblePair() : fFirst( 0 ), fSecond( 0 ) {}
		};
		// --------------------------------


		static const auto kNumOfBytes = ( kMaxNumbers >> 1 ) + ( kMaxNumbers & 0x01 );

		using NibbleArray = std::array< NibblePair, kNumOfBytes >;
		NibbleArray	fData {};		// Tutaj wydajnie przechowujemy półbajty - wymuszamy inicjalizację zerem poprzez dodanie {}


		// Funkcja pomocnicza
		// Zwraca true, gdy index określa pierwszy półbajt
		bool IsFirstNibble( int index ) const { return ( index & 0x01 ) == 0; }		// inline functions
		
		// Zwraca adres liczby w strukturze fData
		auto ReComputeIndex( int index ) const { return index >> 1; }

	public:

		// Część konstrukcyjna
		TLongNumberFor( void ) 
		{ 
			assert( kMaxNumbers > 0 );
			assert( sizeof( NibblePair ) == sizeof( unsigned char ) );		// najpierw sprawdzamy nasz niezmiennik
			assert( sizeof( fData ) == ( kMaxNumbers >> 1 ) + ( kMaxNumbers & 0x01 ) );	// jakieś manipulacje bitami, ale ostrożnie z hierarchią
#if ALLOW_INHERITANCE == 0																		
			assert( sizeof( * this ) == sizeof( fData ) );		// sprawdzanie, czy obiekt nie zawiera więcej niż same dane
#endif
		}

#if ALLOW_INHERITANCE == 1
		virtual ~TLongNumberFor() {}	// Wirtualny destruktor zapewniający dziedziczenie
#endif

	public:

		// Konstruktor konwersji typu – zakłada kolejność bajtów big endian,
		// tj. znak najbardziej na prawo będzie pod indeksem 0,
		// np. "123" zostanie przydzielone jako: 0 ... 0 1 2 3
		TLongNumberFor( const string & s ) 
		{
			assert( s.length() <= kMaxNumbers );	// co zrobić jeśli nie spełnione? Rzucić wyjątek?

			// dedukcja typu szablonu musi dokładnie pasować do przekazanych typów
			auto char_len = std::min( static_cast< decltype( kMaxNumbers ) >( s.length() ), kMaxNumbers );

			if( char_len < 1 )
				return;				// nic do zrobienia, wyjdź

			for( auto i { 0 }; i < char_len; ++ i )
			{
				// Przejdź od znaku najbardziej na lewo w ciągu znaków (kolejność bajtów)
				auto digit { s[ char_len - i - 1 ] - '0' };

				assert( digit >= 0 && digit <= 9 );
				if( ! ( digit >= 0 && digit <= 9 ) )
					return;

				SetNumberAt( i, digit );
			}
		}





		// Konwerter typów – zakłada kolejność big endian,
		// tj. znak najbardziej na prawo będzie pod indeksem 0,
		// np. "123" zostanie przydzielone jako: 0 ... 0 1 2 3
		operator string() const
		{
			string str;

			// Zbuduj ciąg znaków
			for( int i { kMaxNumbers - 1 }; i >= 0; -- i )
			{
				auto a_digit { GetNumberAt( i ) };
				if( a_digit == 0 && str.length() == 0 )
					continue;				// pomiń zera wiodące
				else
					str += '0' + a_digit;	// użyjmy prostego sposobu konwersji
			}

			return str;
		}

	public:

		bool operator == ( const TLongNumberFor & obj )
		{
			// Traktuj tablicę jak serię bajtów
			return std::memcmp( & fData[ 0 ], & obj.fData[ 0 ], sizeof( fData ) ) == 0;
		}

	public:

		// Zwraca cyfrę na danej pozycji
		int GetNumberAt( int position ) const
		{
			assert( position < kMaxNumbers );
			if( position >= kMaxNumbers )
				throw std::out_of_range( "GetNumberAt position out of range" );		// jeśli zła pozycja, zgłoś wyjątek
			return IsFirstNibble( position ) ? fData[ ReComputeIndex( position ) ].fFirst : fData[ ReComputeIndex( position ) ].fSecond;
		}

		void SetNumberAt( int position, int val )
		{
			assert( val >= 0 && val <= 9 );		// sprawdź, czy nie nadużywamy
			assert( position < kMaxNumbers );
			if( position >= kMaxNumbers )
				throw std::out_of_range( "SetNumberAt position out of range" );		// jeśli zła pozycja, zgłoś wyjątek
			IsFirstNibble( position ) ? ( fData[ ReComputeIndex( position ) ].fFirst = val ) : ( fData[ ReComputeIndex( position ) ].fSecond = val );
		}

		// Resetuje wszystkie liczby do 0
		void ClearAll( void )
		{
			fData.fill( NibbleArray::value_type() );	// ustawia wszystko na 0
		}


		// Przeciążony operator indeksu, ale TYLKO do ODCZYTU.
		// Aby móc zapisywać, potrzebujemy wzorca pełnomocnika (patrz niżej).
		const int operator [] ( int position ) const
		{
			assert( position < kMaxNumbers );
			return GetNumberAt( position );		// może zgłaszać wyjątek
		}

#define TURN_ON_PROXY
#ifdef TURN_ON_PROXY   // Poniższy kod jest kompilowany, gdy zdefiniowana jest flaga TURN_ON_PROXY
	private:

		// Prywatny obszar wzorca pełnomocnika

		// -------------------------------------------------------------------
		// Ta zagnieżdżona klasa realizuje wzorzec PEŁNOMOCNIKA
		class RetObjProxy
		{
			public:

				using MotherClass = typename TLongNumberFor< MAX_NUMBERS > ;

			private:


				// Can't use a reference here since
				// an uninitialized reference type data member or const data member 
				// makes the compiler implicitly declare a default constructor as deleted.
				// That would be fine, since we wish a deleted default constructor.
				// 
				// However, it holds also that
				// a const or reference type data member makes the compiler declare a  
				// copy assignment operator as deleted. 
				// This does not work for us - we need a copy assignment. 

				//MotherClass & fMyMother;	// A reference to the mother TLongNumberFor class
				MotherClass * fMyMother {};	// Wskaźnik do klasy matki
					
				int fPosition {};			// Lokalne przechowywanie indeksu dla operatora []

			public:

				// Konstruktor
				// myMother - klasa TLongNumberFor, z którą się łączymy
				// position - pozycja indeksu
				RetObjProxy( MotherClass * myMother, int position )
					: fMyMother( myMother ), fPosition( position )
				{
					assert( fMyMother != nullptr );
					assert( fPosition < MotherClass::kMaxNumbers );
				}


				// Zabroniony konstruktor domyślny
				RetObjProxy( void ) = delete;

				RetObjProxy & operator = ( const RetObjProxy & r )
				{
					return * this;
				}
		
		public:

				// Wywoływany, gdy: int x = id[ 8 ]
				// Operacja prawostronna (odczyt)
				// Operator konwersji do int – dla operacji odczytu
				operator int () const
				{
					assert( fMyMother != nullptr );
					return fMyMother->GetNumberAt( fPosition );
				}

				// Wywoływany, gdy: id[ 8 ] = 5
				RetObjProxy & operator = ( int val )
				{
					assert( fMyMother != nullptr );
					fMyMother->SetNumberAt( fPosition, val );	
					return * this;
				}

				// Kolejny operator przypisania: id[ 8 ] = id[ 7 ]
				RetObjProxy & operator = ( RetObjProxy & r )
				{
					assert( fMyMother != nullptr );
					fMyMother->SetNumberAt( fPosition, r.fMyMother->GetNumberAt( r.fPosition ) );	
					return * this;
				}

		};
		// Koniec pełnomocnika
		// -------------------------------------------------------------------


	public:


		// Głównym celem operatora indeksu w TLongNumberFor
		// jest zwrócenie obiektu pełnomocnika zamiast dowolnej wartości.
		// Zwrócony pełnomocnik będzie zachowywał się inaczej po stronie lewej
		// niż po stronie prawej operatora przypisania.
		RetObjProxy operator [] ( int position )
		{
			assert( position < kMaxNumbers );
			// Tutaj tworzymy obiekt pełnomocnika dostarczającego "this"
			// jako jego klasę "matkę".
			// Zwróć przez wartość (unikanie kopii, gwarantowane w C++17)
			return RetObjProxy( this, position );
		}
	// -------------------------------------------------------------------
#endif
};


/////////////////////////////////////////////////////////////////////////////////
// Operator wstawiania
template < typename auto MAX_NUMBERS >
ostream & operator << ( ostream & o, const TLongNumberFor< MAX_NUMBERS > & longNumb )
{
	for( auto i { TLongNumberFor< MAX_NUMBERS >::kMaxNumbers - 1 }; i >= 0; -- i )
		o << longNumb.GetNumberAt( i );
	return o;
}


/////////////////////////////////////////////////////////////////////////////////
// Operator wyodrębniania
template < typename auto MAX_NUMBERS >
istream & operator >> ( istream & i, TLongNumberFor< MAX_NUMBERS > & longNumb )
{
	string str;
	i >> str;			// odczytaj jako ciąg znaków
	longNumb = str;		// wywołaj konwersję
	return i;
}





