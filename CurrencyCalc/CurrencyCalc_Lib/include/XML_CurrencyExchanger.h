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


#include "CurrencyExchanger.h"

#include <string>
#include <regex>

using std::wregex;


// (1) Using regex
// (2) Processing XML files
// (3) Working with wstrings
// (4) Using state machine


namespace CppBook
{



class XML_CurrencyExchanger : public TCurrencyExchanger
{

	private:


		// Prosta maszyna stanów
		enum class ESearchStates { kIdle, k_Name_Processed, k_Code_Processed, k_BuyingRate_Processed, k_SellingRate_Processed };

	private:

		// Zdefiniujmy wzorce
		// Używamy tutaj surowych formatów tekstu R"( )"
		wregex f_curr_name_pat		{ LR"(<nazwa_waluty>(.+)</nazwa_waluty>)" };
		wregex f_curr_code_pat		{ LR"(<kod_waluty>([[:upper:]][[:upper:]][[:upper:]])</kod_waluty>)" };
		wregex f_buy_rate_pat		{ LR"(<kurs_kupna>([[:d:]]+),([[:d:]]+)</kurs_kupna>)" };      // zamiast 1.27, w Polsce używamy 1,27 (z przecinkiem)
		wregex f_sell_rate_pat		{ LR"(<kurs_sprzedazy>([[:d:]]+),([[:d:]]+)</kurs_sprzedazy>)" };

	public:

		// Zezwól na inne wzorce
		void set_curr_name_pat( const wregex & pat ) { f_curr_name_pat = pat; }
		// ...

	public:

		///////////////////////////////////////////////////////////
		// Wypełnij tabelę walut
		///////////////////////////////////////////////////////////
		//
		// WEJŚCIE:
		//			currencyFile - pełna ścieżka do pliku XML
		//				z wpisami dla walut
		// WYJŚCIE:
		//			rue, jeśli ok, w przeciwnym razie false
		//
		// UWAGI:
		//
		//
		virtual bool	FillCurrencyTableFrom( const wstring & currencyFile );

};




}	// CppBook




