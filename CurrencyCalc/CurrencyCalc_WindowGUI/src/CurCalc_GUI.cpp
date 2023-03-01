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






// grupa dyrektyw #include (FLTK & SL)
#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>

#include <FL/Fl_Button.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Light_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Menu_Button.H>

#include <FL/Fl_Input.H>
#include <FL/Fl_Float_Input.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Multiline_Input.H>

#include <FL/Fl_Slider.H>
#include <FL/fl_ask.H>
#include <FL/forms.H> 

#include <FL/Fl_Value_Output.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Roller.H>
#include <FL/Fl_Dial.H>
#include <FL/Fl_Clock.H>

#include <FL/Fl_Group.H>


// Przydatne dla biblioteki standardowej
#include <vector>
#include <string>


#include <iostream>
#include <filesystem>

#include <typeinfo>
#include <typeindex>

#include <cassert>
	

// deklaracje using
using std::string;
using std::wstring;
using std::vector;



#include "CurCalc_GUI.h"
#include "StringConverters.h"





// Konstruktor parametryczny klasy
CC_GUI::CC_GUI( XCE & xce, const wstring & fromCurrency /*= L"PLN"*/ ) 
	:	fXML_CurrencyExchanger( xce ), 
		fFromCurrencyCode( fromCurrency ) 
{
}
// Destruktor nic nie robi – na wypadek dziedziczenia zdefiniowany jako wirtualny	
CC_GUI::~CC_GUI() 
{
}


// FUNKCJA WYWOŁANIA ZWROTNEGO – NIE modyfikuj !!!
void CC_GUI::theButtonCallback( Fl_Widget * widgetPtr, void * obj ) 
{
	// Konwertuje wskaźnik wejściowy na obiekt naszej klasy
	CC_GUI * theObj = reinterpret_cast< CC_GUI * >( obj );

	// Wywołaj funkcję obsługi przycisku
	theObj -> Action_On_Button();
}


///////////////////////////////////////////////////////////
// Lokalna funkcja do przetwarzania żądań przycisku
///////////////////////////////////////////////////////////
//		
// WEJŚCIE:
//			brak
//		
// WYJŚCIE:
//			brak
//		
// UWAGI:
//		
//	
bool CC_GUI::Action_On_Button( void )
{
	try
	{

		///////////////////////////////////
		// Pozyskaj wartość z widżetu edycji
		const char * editWidget_Text = fEditWidget->value();	// Najpierw pozyskaj jego tekst

			
		double from_val = stod( string( editWidget_Text ) );

		const Fl_Menu_Item * menu_item =	fChoiceWidget->mvalue();

		wstring to_code = Code_2_CurrencyKey( (unsigned long) menu_item->user_data() );


		// Jesteśmy gotowi do konwersji
		if( double to_val {}; fXML_CurrencyExchanger.Convert( fFromCurrencyCode, from_val, to_code, to_val ) == true )
		{
			fStaticEditWidget->value( to_val );
		
			// Zaktualizuj tekst
			fStaticEditWidget->copy_label( to_string( to_code ).c_str() );

			fMainWindow->redraw();
		}

		return true;			
			
	}
	catch( ... )
	{
		return false;
	}


}


///////////////////////////////////////////////////////////
// Konwertuje trzyznakowy kod na jedno słowo z bajtami
// ustawionymi na znaki kodu.
///////////////////////////////////////////////////////////
//		
// WEJŚCIE:
//			wstr - obiekt dwubajtowego tekstu z 3-literowym kodem
//		
// WYJŚCIE:
//			kod w jednym słowie
//		
// UWAGI:
//		
//	
unsigned long	CC_GUI::CurrencyKey_2_Code( const wstring & wstr )
{
	string str( to_string( wstr ) );		// wstring ==> string
	return str[ 0 ] << 16 | str[ 1 ] << 8 | str[ 2 ];		
}

///////////////////////////////////////////////////////////
// Konwertuje jednosłowowy kod waluty na kod dwubajtowego tekstu
///////////////////////////////////////////////////////////
//		
// WEJŚCIE:
//			code - słowo z literami w każdym bajcie, zaczynając
//				od najmniej znaczącego bajtu
//		
// WYJŚCIE:
//			wstring z literami ze słowa wejściowego
//		
// UWAGI:
//		
//	
wstring			CC_GUI::Code_2_CurrencyKey( const unsigned long & code )
{
	const int kArrSize { 3 };
	char arr[ kArrSize ] = { 0 };
	arr[ 2 ] = code & 0xFF;
	arr[ 1 ] = code >> 8 & 0xFF;
	arr[ 0 ] = code >> 16 & 0xFF;
	//return wstring( arr, arr + kArrSize );
	return to_wstring( string( arr, arr + kArrSize ) );
}




///////////////////////////////////////////////////////////
// Ta funkcja tworzy graficzny interfejs użytkownika
///////////////////////////////////////////////////////////
//		
// WEJŚCIE:
//			brak
//		
// WYJŚCIE:
//			kod stanu FLTK
//		
// UWAGI:
//		
//	
int CC_GUI::Create_GUI( void )
{
	///////////////////////////////////////////////
	//// Utwórz okno główne
	const int kMainWin_w = 400;
	const int kMainWin_h = 250;
	const string kMainWin_Caption( "CurrencyCalc (Polish National Bank)" );
	Fl_Window	main_win( kMainWin_w, kMainWin_h, kMainWin_Caption.c_str() );

	fMainWindow = & main_win;					// połącz poprzez ogólnie dostępną składową klasy CC_GUI


	///////////////////////////////////////////////
	//// Pewne stałe
	const int kWidgetSeparator_h = 75;
	const int kWidgetSeparator_v = 25;

	/////////////////////////////////////////////
	// Dodaj widżet theEdit
	const int kEdit_x = 100;
	const int kEdit_y = 50;
	const int kEdit_w = 100;
	const int kEdit_h = 30;

	const string kEdit_Caption( "From " + string( to_string( fFromCurrencyCode ) ) );
	Fl_Float_Input	theEdit( kEdit_x, kEdit_y, kEdit_w, kEdit_h, kEdit_Caption.c_str() );
	theEdit.value( "0" );		// wartość początkowa

	fEditWidget = & theEdit;					// połącz poprzez ogólnie dostępną składową klasy CC_GUI


	//auto edit_tuple = Create_MainWindow( make_tuple( 0, 0, kMainWin_w, kMainWin_h ) );

	/////////////////////////////////////////////
	// Dodaj widżet pola kombi
	const int kChoiceWidget_x = kEdit_x + kEdit_w + kWidgetSeparator_h;
	const int kChoiceWidget_y = kEdit_y;
	const int kChoiceWidget_w = kEdit_w;
	const int kChoiceWidget_h = kEdit_h;
	
	
	vector< Fl_Menu_Item >	menuItemVec;


	const XCE::CurrencyMap & curMap = fXML_CurrencyExchanger.GetCurrencyMap();

	assert( curMap.size() > 0 );
	
	// Kolekcja tekstu dla elementów menu FLTK
	std::vector< std::string >		menuItemTexts;



	transform(	curMap.begin(), curMap.end(), back_inserter( menuItemTexts ), 
				[] ( const auto & cur ) { return to_string( cur.second.GetCurrName() ); } );


	int cntr { 0 };
	for( const auto & [ key, currency ] : fXML_CurrencyExchanger.GetCurrencyMap() )
	{
		menuItemVec.push_back( { menuItemTexts[ cntr ++ ].c_str(), 0, 0, reinterpret_cast< void * >( CurrencyKey_2_Code( key ) ) } );
	}


	// Umieść strażnika na liście menu
	if( menuItemVec.size() > 0 )
		menuItemVec[ menuItemVec.size() - 1 ] = { 0 }; // Nadpisz ostatni wpis
	else
		menuItemVec.push_back( { 0 } );



	const string kChoiceWidget_Caption( "To " );
	Fl_Choice theChoiceWidget( kChoiceWidget_x, kChoiceWidget_y, kChoiceWidget_w, kChoiceWidget_h, kChoiceWidget_Caption.c_str() );
	theChoiceWidget.menu( & menuItemVec[ 0 ] );

	fChoiceWidget = & theChoiceWidget;			// Połącz poprzez zmienną składową


	/////////////////////////////////////////////
	// Dodaj stałe widżetu theStaticEdit
	const int kStaticEdit_x = kEdit_x;
	const int kStaticEdit_y = kEdit_y + kEdit_h + kWidgetSeparator_v;
	const int kStaticEdit_w = kEdit_w;
	const int kStaticEdit_h = kEdit_h;

	const string kStaticEdit_Caption( "" );
	Fl_Value_Output		theStaticEdit( kStaticEdit_x, kStaticEdit_y, kStaticEdit_w, kStaticEdit_h, kStaticEdit_Caption.c_str() );
	int staticValue = 0;
	theStaticEdit.value( staticValue );

	fStaticEditWidget = & theStaticEdit;		// Połącz poprzez zmienną składową


	/////////////////////////////////////////////
	// Dodaj przycisk
	const int kButtonEdit_x = kStaticEdit_x;
	const int kButtonEdit_y = kStaticEdit_y + kStaticEdit_h + kWidgetSeparator_v;
	const int kButtonEdit_w = kStaticEdit_w;
	const int kButtonEdit_h = kStaticEdit_h;

	const string kButtonCaption( "ReCalc" );

	Fl_Return_Button theButton( kButtonEdit_x, kButtonEdit_y, kButtonEdit_w, kButtonEdit_h, kButtonCaption.c_str() ); 

	theButton.callback( theButtonCallback, this );		// Podłącz funkcję wywołania zwrotnego

	
	/////////////////////////////////////////////
	// Zakończ dodawanie nowych widżetów
	main_win.end();
	main_win.show();

	
	/////////////////////////////////////////////
	// Po zamknięciu wszystkich okien zwraca zero
	return Fl::run();		

}





// ===============================================================================

