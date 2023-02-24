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



#pragma once



#include <cassert>
#include <vector>
#include <memory>



namespace CppBook
{





// ==============================================================================================

// Definicja struktury danych stosu
template < typename T, auto MaxElems = 1000 >
class TStackFor
{
	public:

		using value_type = T;

	private:

		using DataContainer = std::vector< value_type >;

		DataContainer		fData;

	public:

		// Potrzebujemy tu dodatkowego słowa typename
		using size_type = typename DataContainer::size_type;


	public:

		auto GetStackSize( void ) const { return fData.size(); }

	public:


		///////////////////////////////////////////////////////////
		// Ta funkcja umieszcza element na stosie
		///////////////////////////////////////////////////////////
		//		
		// WEJŚCIE:
		//			new_elem - referencja do elementu do umieszczenia.
		//				Tak naprawdę na stosie umieszczana jest
		//				jego kopia.
		//		
		// WYJŚCIE:
		//			true - jeśli operacja wykona się pomyślnie,
		//			false - błąd z powodu niewystarczającego
		//				miejsca na stosie (np. zbyt wiele 
		//				elementów)
		//		
		// UWAGI:
		//		
		//		
		bool Push( const value_type & new_elem );



		///////////////////////////////////////////////////////////
		// Ta funkcja usuwa element ze stosu
		///////////////////////////////////////////////////////////
		//		
		// WEJŚCIE:
		//			ret_elem - referencja do obiektu, który 
		//				zostanie skopiowany z górnego elementu
		//				na stosie. Następnie ten górny element stosu
		//				zostanie z niego usunięty.
		//		
		// OUTPUT:
		//			true - gdy operacja zakończy się sukcesem,
		//			false - błąd z powodu pustego stosu
		//		
		// REMARKS:
		//		
		bool Pop( value_type & ret_elem );


};



///////////////////////////////////////////////////////////
// This functions puts an element onto the stack
///////////////////////////////////////////////////////////
//		
// INPUT:
//			new_elem - a reference to the element to
//				be put. Actually its copy is put onto
//				the stack.
//		
// OUTPUT:
//			true - if operation successful,
//			false - failure, due to insufficient
//				space on the stack (e.g. too many 
//				elements)
//		
// REMARKS:
//		
//		
template < typename T, auto MaxElems >
bool TStackFor< T, MaxElems >::Push( const value_type & new_elem )
{
	if( GetStackSize() == MaxElems )
		return false;

	fData.emplace_back( new_elem );

	return true;
}




///////////////////////////////////////////////////////////
// This functions takes and removes an element from the stack
///////////////////////////////////////////////////////////
//		
// INPUT:
//			ret_elem - a reference to the object which
//				will be copied with a topmost element
//				from the stack. Then the topmost element
//				is removed from the stack.
//		
// OUTPUT:
//			true - if operation successful,
//			false - failure, due to empty stack
//		
// REMARKS:
//	
template < typename T, auto MaxElems >
bool TStackFor< T, MaxElems >::Pop( value_type & ret_elem )
{
	if( GetStackSize() == 0 )
		return false;

	ret_elem = fData.back();	// Skopiuj górny element
	fData.pop_back();			// Pozbądź się ostatniego elementu

	return true;
}

}		// Koniec przestrzeni nazw CppBook



// ----------------------------------------------------




namespace CppBook
{



// Specjalizacja stosu do operowania z użyciem std::unique_ptr
template < typename T, auto MaxElems >
class TStackFor< std::unique_ptr< T >, MaxElems >
{
	public:

		using value_type = std::unique_ptr< T >;

	public:

		using DataContainer = std::vector< value_type >;
		
	private:

		DataContainer		fData;

	public:

		DataContainer &	GetDataContainer( void ) { return fData; }

	public:

		// Tutaj potrzebujemy dodatkowego słowa typename
		using size_type = typename DataContainer::size_type;

	public:

		auto GetStackSize( void ) const { return fData.size(); }

	public:


		///////////////////////////////////////////////////////////
		// Ta funkcja umieszcza elementy na stosie
		///////////////////////////////////////////////////////////
		//		
		// WEJŚCIE:	new_elem - inteligentny wskaźnik do obiektu, który
		//				ma zostać przeniesiony 
		//				na stos.
		//		
		// WYJŚCIE:	true – gdy operacja zakończy się sukcesem,
		//			false – błąd, z powodu niewystarczającej
		//				ilości miejsca na stosie (np. za dużo 
		//				elementów)
		//		
		bool Push( value_type new_elem )
		{
			if( GetStackSize() == MaxElems )
				return false;

			fData.emplace_back( std::move( new_elem ) );
			// new_elem jest teraz pusty

			return true;
		}



		///////////////////////////////////////////////////////////
		// Ta funkcja pozyskuje i usuwa element ze stosu
		///////////////////////////////////////////////////////////
		//		
		// WEJŚCIE:	new_elem – referencja do obiektu, który
		//				zostanie skopiowany za pomocą elementu na
		//				szczycie stosu. Następnie element ten
		//				zostaje usunięty ze stosu.
		//		
		// WYJŚCIE:	true – gdy operacja zakończy się sukcesem,
		//			false – błąd, z powodu pustego stosu
		//		
		bool Pop( value_type & ret_elem )
		{
			if( GetStackSize() == 0 )
				return false;

			ret_elem.reset( fData.back().release() );	// ponownie podłącz wskaźniki
			fData.pop_back();		// pozbądź się ostatniego (pustego) elementu

			return true;
		}



};


template < typename T >
using UP_Stack_1000 = TStackFor< std::unique_ptr< T >, 1000 >;


}		// End of the CppBook namespace





