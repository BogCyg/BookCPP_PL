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



#include <vector>
#include <string>



#include "XML_CurrencyExchanger.h"
#include "CurrencyCalcPlayGround.h"



// Deklaracje zapowiadające
class Fl_Choice;		
class Fl_Float_Input;
class Fl_Value_Output;	
class Fl_Window;		
class Fl_Widget;



namespace OL_CE = CurrExchanger::OnLine_CurrExchanger;



// CC - Currency Calculator
class CC_GUI
{
	private:

		// Wskaźniki do widżetów FLTK
		Fl_Choice *			fChoiceWidget {};
		Fl_Float_Input *	fEditWidget {};
		Fl_Value_Output	*	fStaticEditWidget {};
		Fl_Window *			fMainWindow {};				



	private:

		// Interfejs do naszego komponentu kalkulatora walut

		using XCE = OL_CE::XML_CurrencyExchanger;


		XCE &		fXML_CurrencyExchanger;

		// Początkowy kod waluty referencyjnej
		std::wstring		fFromCurrencyCode;


	public:

		CC_GUI( XCE & xce, const std::wstring & fromCurrency = L"PLN" );
	
		virtual ~CC_GUI();

	private:

		///////////////////////////////////////////////////////////
		// FUNKCJA WYWOŁANIA ZWROTNEGO – NIE modyfikować !!!
		///////////////////////////////////////////////////////////
		//		
		// WEJŚCIE:
		//			widgetPtr - wskaźnik do widżetu przycisku
		//			obj - wskaźnik "this" do obiektu CC_GUI
		//		
		// WYJŚCIE:
		//			brak
		//		
		// UWAGI:
		//			Statyczna funkcja do umieszczenia jako wywołanie zwrotne przycisku FLTK 
		//			Deleguje akcję do Action_On_Button().
		//	
		static void theButtonCallback( Fl_Widget * widgetPtr, void * obj );

	protected:

		///////////////////////////////////////////////////////////
		// Lokalna funkcja do przetwarzania żądań przycisku
		///////////////////////////////////////////////////////////
		//		
		// WEJŚCIE:
		//			brak
		//		
		// WYJŚCIE:
		//			true, jeśli ok
		//		
		// UWAGI:
		//		
		//	
		virtual bool Action_On_Button( void );

	private:

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
		unsigned long	CurrencyKey_2_Code( const std::wstring & wstr );

		///////////////////////////////////////////////////////////
		// Konwertuje jednosłowowy kod waluty na kod dwubajtowego tekstu
		///////////////////////////////////////////////////////////
		//		
		// INPUT:
		//			code - słowo z literami w każdym bajcie, zaczynając
		//				od najmniej znaczącego bajtu
		//		
		// OUTPUT:
		//			wstring z literami ze słowa wejściowego
		//		
		// REMARKS:
		//		
		//	
		std::wstring			Code_2_CurrencyKey( const unsigned long & code );



	public:


		///////////////////////////////////////////////////////////
		// Ta funkcja tworzy graficzny interfejs użytkownika
		// i uruchamia aplikację.
		///////////////////////////////////////////////////////////
		//		
		// WEJŚCIE:
		//			brak
		//		
		// WYJŚCIE:
		//			kod stanu FLTK
		//		
		// UWAGI:
		//			Ta funkcja nie kończy działania. Wyjście tylko
		//			z poziomu aplikacji
		//	
		virtual int Create_GUI( void );



};			// koniec CC_GUI

