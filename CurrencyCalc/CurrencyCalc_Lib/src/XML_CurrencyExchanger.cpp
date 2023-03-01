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



#include "XML_CurrencyExchanger.h"
#include <fstream>
#include <filesystem>

using namespace std;

namespace CppBook
{


bool	XML_CurrencyExchanger::FillCurrencyTableFrom( const wstring & currencyFile )
{
	wifstream	inFile( std::filesystem::path( currencyFile ), std::ios::binary );

	if( ! inFile.is_open() )
		return false;				// nie można otworzyć pliku wejściowego

	// Ustaw prawidłowe kodowanie znaków dla tego pliku - z NBP wiemy, że to 88592 (ale ogólnie trzeba sprawdzić)
	inFile.imbue( std::locale( "pl_PL.iso88592" ) );	// jeśli nie działa to sprawdź zainstalowane "locale" w systemie
														// Np. na UBUNTU
														// 		locale -a
														// jeśli nie ma "pl_PL.iso88592", to zainstaluj
														// 		sudo locale-gen pl_PL

	// Czytaj linia po linii i szukaj wzorców


	ESearchStates	state = ESearchStates::kIdle;

	// Przechowuje obecnie przetwarzaną linię XML
	wstring line;

	// Przechowuje obecne dopasowanie i poddopasowania regex
	wsmatch	match_res;

	// Tu zostaną zebrane częściowe dopasowania dla rekordu waluty
	wstring curr_code, curr_name, buy_rate_str, sell_rate_str;

	// Czytaj parametry jeden po drugim
	while( getline( inFile, line ) )
	{

		switch( state )
		{
			case ESearchStates::kIdle:

				if( regex_search( line, match_res, f_curr_name_pat ) && match_res.size() > 1 )
				{
					// Ok, kod waluty znaleziony. Zachowajmy go
					// wymagaj przynajmniej jednego podwyrażenia
					curr_name = match_res[ 1 ];		// weź pierwsze poddopasowanie
					
					// Dla łatwiejszego przetwarzania, zamień znaki białe
					replace( curr_name.begin(), curr_name.end(), L' ', L'-');

					state = ESearchStates::k_Name_Processed;	// zmień stan 
				}				
				
				break;

			case ESearchStates::k_Name_Processed:

				if( regex_search( line, match_res, f_curr_code_pat ) && match_res.size() > 1 )
				{
					// Ok, kod waluty znaleziony. Zachowajmy go
					// wymagaj przynajmniej jednego podwyrażenia
					curr_code = match_res[ 1 ];		// weź pierwsze poddopasowanie

					state = ESearchStates::k_Code_Processed;	// zmień stan 
				}				
				
				break;

			case ESearchStates::k_Code_Processed:

				// Spróbuj dopasować opcję kupna
				if( regex_search( line, match_res, f_buy_rate_pat ) && match_res.size() > 2 )
				{
					// Ok, kod waluty znaleziony. Zachowajmy go
					// wymagaj przynajmniej jednego podwyrażenia
					buy_rate_str = wstring( match_res[ 1 ] ) + wstring( L"." ) + wstring( match_res[ 2 ] );		// złącz poddopasowania

					state = ESearchStates::k_BuyingRate_Processed;	// zmień stan
				}		

				break;

			case ESearchStates::k_BuyingRate_Processed:

				// Spróbuj dopasować opcję sprzedaży
				if( regex_search( line, match_res, f_sell_rate_pat ) && match_res.size() > 2 )
				{
					// Ok, kod waluty znaleziony. Zachowajmy go
					// wymagaj przynajmniej jednego podwyrażenia
					sell_rate_str = wstring( match_res[ 1 ] ) + wstring( L"." ) + wstring( match_res[ 2 ] );	// złącz poddopasowania

					state = ESearchStates::k_SellingRate_Processed;	// zmień stan
				}	

				break;

			case ESearchStates::k_SellingRate_Processed:

				// Jesteśmy gotowi do wstawienia nowego rekordu waluty
				try
				{	
					// Może zgłosić wyjątek, np. pusty ciąg znaków, zły format itd.
					AddCurrency( { curr_code, curr_name, stod( buy_rate_str ), stod( sell_rate_str ) } );
				}
				catch( ... )
				{
					;
				}

				state = ESearchStates::kIdle;		// przejdź do podstawowego stanu

				break;

			default:
				assert( false );	// nie powinniśmy tu być
				break;
		}


	}



	return true;
}


}	// CppBook



