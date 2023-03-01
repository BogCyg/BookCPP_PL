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



#pragma once


#include "Currency.h"

#include <map>





namespace CppBook
{


class TCurrencyExchanger
{
	public:

		// struktura danych klucz-wartość
		using CurrencyMap = std::map< wstring, TCurrency >;		

	private:

		CurrencyMap							fCurrencyMap;	// mapa do przechowywania obiektów TCurrency

	public:

		// Niech kompilator je wygeneruje
		TCurrencyExchanger( void ) = default;
		virtual ~TCurrencyExchanger() = default;  // wirtualny destruktor do dziedziczenia

	public:

		///////////////////////////////////////////////////////////
		// Ta funkcja konwertuje wartość w jednej walucie
		// na wartość w innej walucie
		///////////////////////////////////////////////////////////
		//
		// WEJŚCIE:
		//			from_key - 3-znakowy kod waluty (USD, PLN itd.)
		//			from_val - wartość do skonwertowania
		//			to_key - kod waluty docelowej
		//			to_val - wartość wynikowa
		//
		// WYJŚCIE:
		//			true jeśli ok, w przeciwnym wypadku false
		//
		// UWAGI:
		//			Jeśli from_key lub to_key nie jest zawarte w mapie,
		//			funkcja zgłosi wyjątek. Kod danej waluty
		//			cmoże zostać sprawdzony poprzez wywołanie funkcji składowej FindCurrency
		//
		bool Convert( const wstring & from_key, const double from_val, const wstring & to_key, double & to_val ) const;


		///////////////////////////////////////////////////////////
		// Funkcja pomocnicza do uzyskiwania dostępu tylko do odczytu dla fCurrencyMap
		///////////////////////////////////////////////////////////
		//
		// WEJŚCIE:
		//			brak
		// WYJŚCIE:
		//			wewnętrzna struktura danych mapy (tylko do odczytu)
		//
		// UWAGI:
		//
		//
		const CurrencyMap & GetCurrencyMap( void ) const { return fCurrencyMap;	}


		///////////////////////////////////////////////////////////
		// Znajdź i zwróć walutę na podstawie jej kodu.
		// Zwraca true jeśli ok lub false, gdy nie może jej znaleźć.
		///////////////////////////////////////////////////////////
		//
		// WEJŚCIE:
		//			currency_code - 3-literowy kod waluty, taki
		//				ak "USD", "EUR", itd. 
		//			outCurrency - zawiera znalezioną walutę, jeśli zwrócono true
		// WYJŚCIE:
		//			true jeśli ok lub false, jeśli nie może znaleźć
		//
		// UWAGI:
		//
		//
		bool FindCurrency( const wstring & currency_code, TCurrency & outCurrency ) const;


		///////////////////////////////////////////////////////////
		// Dodaje nowy rekord waluty do bazy danych
		///////////////////////////////////////////////////////////
		//
		// WEJŚCIE:
		//			new_currency - nowy rekord waluty. Jeśli już istnieje 
		//				zostaje zastąpiona tym wpisem
		// WYJŚCIE:
		//			brak
		//
		// UWAGI:
		//
		//
		void AddCurrency( const TCurrency & new_currency );

	private:

		// Funkcje zaprzyjaźnione do odczytu i zapisu fCurrencyMap
		friend std::wostream & operator << ( std::wostream & o, const TCurrencyExchanger & c );
		friend std::wistream & operator >> ( std::wistream & i, TCurrencyExchanger & c );
};



}		// Koniec przestrzeni nazw CppBook

