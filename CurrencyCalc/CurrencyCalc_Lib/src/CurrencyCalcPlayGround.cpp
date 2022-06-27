﻿// ==========================================================================
//
// Software written by Boguslaw Cyganek (C) to be used with the book:
// INTRODUCTION TO PROGRAMMING WITH C++ FOR ENGINEERS
// Published by Wiley, 2020
//
// The software is supplied as is and for educational purposes
// without any guarantees nor responsibility of its use in any application. 
//
// ==========================================================================



/////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cassert>
#include <optional>
#include <filesystem>


#include "CurrencyCalcPlayGround.h"


using std::wstring, std::wcout, std::wcin, std::endl;
using std::string, std::wifstream, std::wofstream;
using std::ostream_iterator;



namespace CurrExchanger
{

	wstring initDefaultFileName { L"Currency.txt" };


	using CurrExch_Optional = std::optional< TCurrencyExchanger >;


	///////////////////////////////////////////////////////////
	// Tworzy i inicjalizuje obiekt TCurrencyExchanger
	///////////////////////////////////////////////////////////
	//
	// WEJŚCIE:
	//		initFileFullPath - pełna ścieżka do pliku ini zawierającego
	//			sformatowane informacji dla walut i kursów wymiany
	// WYJŚCIE:
	//		Istnieją dwie opcje dla zwracanego obiektu CurrExch_Optional:
	//			- Jest to TCurrencyExchanger, gdy poprawnie zbudowany
	//			- pusty obiekt CurrExch_Optional, jeśli nie można go utworzyć 
	//
	auto CreateCurExchanger( const wstring & initFileFullPath ) -> CurrExch_Optional
	{
		wifstream	inFile( initFileFullPath );

		if( inFile.is_open() == false )
			return CurrExch_Optional();	// brak pliku ini, brak obiektu, co zwrócić?

		TCurrencyExchanger	currencyExchangerObj;

		// Wczytaj dane z pliku
		inFile >> currencyExchangerObj;

		return CurrExch_Optional( currencyExchangerObj );
	}


	void DisplayAllCurrencies( const TCurrencyExchanger & currencyExchangerObj )
	{
		// Wyświetl dostępne waluty
		const TCurrencyExchanger::CurrencyMap & cur_map = currencyExchangerObj.GetCurrencyMap();

		wcout << L"Available currencies:" << endl;

		// Użyj powiązania strukturalnego
		for( const auto & [ key, val ] : cur_map )
			wcout << val.GetCurrKey() << L" : " << val.GetCurrName() << endl;

		wcout << endl;
	}


	void DisplayCurrentTime( void )
	{
		using timer = std::chrono::system_clock;
		std::time_t time_point = timer::to_time_t( timer::now() );
		string time_str( std::ctime( & time_point ) );
		wcout << wstring( time_str.begin(), time_str.end() );	// string ==> wstring
	}

	// Dokonaj wymiany waluty na podstawie poleceń użytkownika.
	void UserInterface( const TCurrencyExchanger & currencyExchangerObj )
	{

		// Pracuj z użytkownikiem
		wstring answer;
		do
		{
			try
			{
				wstring from_curr, to_curr;
				wstring from_val {};	// double byłoby ok, ale co wprowadzi użytkownik...
				double to_val {};

				wcout << L"Enter from currency code: "; wcin >> from_curr; wcout << endl;
				wcout << L"Enter value to exchannge: "; wcin >> from_val; wcout << endl;
				wcout << L"Enter to currency code  : "; wcin >> to_curr; wcout << endl;
	
				if( currencyExchangerObj.Convert( from_curr, stod( from_val ), to_curr, to_val ) == true )
					wcout << from_val << L" " + from_curr + L" ==> " << to_val << L" " + to_curr << endl;
				else
					wcout << L"Cannot convert these currencies" << endl;
			}
			catch( ... )
			{
				wcout << L"Error - wrong input." << endl;
			}

			// Zapytaj użytkownika, co robić dalej
			wcout << endl << L"New conversion [y/n]?"; 
			wcin >> answer;
			wcout << endl;


		} while( answer.find( L"y" ) != wstring::npos );


	}

	// Uruchom, jeśli mamy już obiekt TCurrencyExchanger
	void Run( const TCurrencyExchanger & currExchObj )
	{
		wcout << "*** Welcome to the currency exchanger ***" << endl;
		DisplayCurrentTime();
		wcout << endl;

		DisplayAllCurrencies( currExchObj );

		UserInterface( currExchObj );
	}


	// Wszystkie akcje
	void Run( void )
	{
		namespace fs = std/*::experimental*/::filesystem;

		wstring iniPath( fs::current_path() / fs::path( initDefaultFileName ) );

		// Najpierw spróbuj pozyskać bieżący obiekt
		if( CurrExch_Optional all_my_options { CreateCurExchanger( iniPath ) }; all_my_options )
		{
			Run( * all_my_options );
		}
		else
		{
			wcout	<< L"Error, check Currency.txt file." << endl
					<< L"Exiting ..." << endl;
		}
	}


}		// Koniec przestrzeni nazw CurrExchanger


/////////////////////////////////////////////////////////




#include "XML_CurrencyExchanger.h"
#include "HTTP_File.h"



using CppBook::HTTP_File_Handle, CppBook::TCurrency;



namespace CurrExchanger
{

// A version that can load from a HTTP downloaded XML file.
namespace OnLine_CurrExchanger
{
	// Internet address of an external xml file
	wstring nbp_addr { L"http://www.nbp.pl/kursy/xml/LastC.xml" };	
	
	// Name of a temporary local XML file
	wstring local_xml_file_name { L"LastC.xml" };		
	
	// A flag indicating the current OS
	HTTP_File_Handle::EHandledSystems kMyOS { HTTP_File_Handle::EHandledSystems::kWindows };



	bool CurExchanger_DownloadCurrencies( const wstring & http_addr, const wstring & local_XML_FullPath )
	{
		HTTP_File_Handle		http_client( kMyOS );
		return http_client.Load_HTTP_File( nbp_addr, local_XML_FullPath );
	}


	void CurExchanger_SaveInitFile( const XML_CurrencyExchanger & obj, const wstring & initFileFullPath )
	{
		// Save to the init file
		// Use default file to load currencies
		wofstream	outFile( initFileFullPath );
		const XML_CurrencyExchanger::CurrencyMap & cur_map = obj.GetCurrencyMap();
		transform(	cur_map.cbegin(), cur_map.cend(), 
					ostream_iterator< TCurrency, wchar_t >( outFile, L"\n" ), 
					[] ( const XML_CurrencyExchanger::CurrencyMap::value_type & vt ) { return vt.second; } );	
	}


	
	//using XML_CurrExch_Optional = std::optional< XML_CurrencyExchanger >;



	// There are two options for the return object:
	// - It is either TCurrencyExchanger if properly built
	// - or empty CurrExch_Optional if cannot create 
	auto CreateCurExchanger( const wstring & http_XML_FileName, const wstring & initFileFullPath ) -> XML_CurrExch_Optional
	{
		XML_CurrencyExchanger	currencyExchangerObj;

		namespace fs = std::filesystem;		

		// Create name of a local XML file - its parent is from initFileFullPath 
		wstring local_xml_full_path( fs::path( initFileFullPath ).parent_path() / local_xml_file_name );

		if( CurExchanger_DownloadCurrencies( http_XML_FileName, local_xml_full_path ) == true &&
			currencyExchangerObj.FillCurrencyTableFrom( local_xml_full_path ) == true )
		{
			// Success, object initialized from Internet
				
			// Add the reference currency (PLN) (0xB3 is Polish letter "l-crossed")
			currencyExchangerObj.AddCurrency( { L"PLN", L"z\xB3oty-polski", 1.0, 1.0 } );
			//currencyExchangerObj.AddCurrency( { L"PLN", L"zloty-polski", 1.0, 1.0 } );

			// Update the ini file with new data
			CurExchanger_SaveInitFile( currencyExchangerObj, initFileFullPath );
		}
		else
		{
			// Cannot initialize from the Internet, 
			// so, as a last resort, let's look for a local ini file
			
			wifstream	inFile( initFileFullPath );

			if( inFile.is_open() == false )
				return XML_CurrExch_Optional();	// no init file, no object, what to return?

			// Read data from the file
			inFile >> currencyExchangerObj;
		}

		return XML_CurrExch_Optional( currencyExchangerObj );
	}


	// All actions
	void Run( void )
	{
		namespace fs = std/*::experimental*/::filesystem;

		wstring iniPath( fs::current_path() / fs::path( initDefaultFileName ) );

		// First try to get the currency object
		if( XML_CurrExch_Optional all_my_options { CreateCurExchanger( nbp_addr, iniPath ) }; all_my_options )
		{
			CurrExchanger::Run( * all_my_options );		// functions do not overload over namespaces
		}												// so we have to use CurrExchanger::
		else
		{
			wcout	<< L"Error, check Currency.txt file." << endl
					<< L"Exiting ..." << endl;
		}
	}

}	// end of OnLine_CurrExchanger

}	// end of CurrExchanger


