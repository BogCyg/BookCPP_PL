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



#include <string>
#include <array>
#include <list>
#include <iostream>
#include <cassert>




namespace EventSystem
{


	// Klasa bazowa definiująca procedurę obsługi zdarzenia (handler)
	// Może być również łączona na liście
	class THandler
	{

	public:

		virtual ~THandler() = 0					// virtual dla poprawnego dziedziczenia
		{ std::cout << "~H()" << std::endl; }	// Czysto wirtualne funkcje mogą mieć ciało
												// Główna funkcja obsługi zdarzenia ==> obiekt funkcyjny
		virtual void operator () ( void ) = 0;	// Czysto wirtualny w celu zdefiniowania INTERFEJSU dla klas pochodnych

	};




	class TEventHandlers
	{
	public:

		enum class EEvent { kReset, kDivByZero, kExternal, kSpurious, kSentinel };


		using TH_UP = std::unique_ptr< THandler >;
		using HandlerList = std::list< TH_UP >;

		// Tablica zawierająca listy obiektów pochodzących od THandler
		using EventVector = std::array< HandlerList, static_cast< int >( EEvent::kSentinel ) >;

	private:

		EventVector		fEventVector;

	public:

		void AttachHandler_4_Event( EEvent event_to_attach, TH_UP new_handler )
		{
			assert( static_cast< int >( event_to_attach ) < static_cast< int >( EEvent::kSentinel ) );
			fEventVector[ static_cast< int >( event_to_attach ) ].emplace_back( std::move( new_handler ) );	// lub emplace_front
		}

		// Uruchom obsługę przyłączoną do zdarzenia
		virtual void operator () ( const HandlerList & list_of_handlers )
		{

			for( const auto & handler : list_of_handlers )
				( * handler )(); // wywołaj operator funkcyjny za pomocą wskaźnika do obiektu obsługi
		}

		virtual void operator () ( EEvent event )
		{
			// Jeden ze sposobów na wywołanie operatora funkcyjnego 
			operator () ( fEventVector[ static_cast< int >( event ) ] );
		}

		// Uruchom wszystko
		virtual void operator () ( void )
		{
			for( const auto & list : fEventVector )
				( * this ) ( list );	// Wywołaj operator () ( EEvent event )
										//operator() ( list );
		}


	};



	void EventHandlers_Test( void )
	{

		TEventHandlers		theHandlerBoard;


		// -------------------
		// Utwórz kilka wariantów obsługi zdarzeń

		class HA : public THandler
		{
			std::string	fStr;

		public:

			HA( std::string s = "" ) : fStr( s ) {}
			virtual ~HA() { std::cout << "~HA()" << std::endl; }

			void operator () ( void ) override	// również jest virtual, ale do wyrażenia tego wystarczy override
			{
				std::cout << "I'm HA with text: " << fStr << std::endl;
			}
		};

		class HB : public THandler
		{
			int	fVal;

		public:

			HB( int v = 0 ) : fVal( v ) {}
			virtual ~HB() { std::cout << "~HB()" << std::endl; }

			void operator () ( void ) override 
			{
				std::cout << "I'm HB: " << std::dec << fVal << " = " << std::hex << fVal << std::endl;
			}
		};
		// -------------------

		HA ha( "Standalone HA" );
		ha();						// Wywołaj operator funkcyjny na obiekcie ha

		( HB( 789 ) )();			// Wywołaj operator funkcyjny na obiekcie tymczasowym HB

		std::cout << std::endl;

		// Teraz dołącz obiekty obsługi do dostępnych slotów zdarzeń

		theHandlerBoard.AttachHandler_4_Event( TEventHandlers::EEvent::kReset, std::make_unique< HA >( "Reset 0" ) );
		theHandlerBoard.AttachHandler_4_Event( TEventHandlers::EEvent::kReset, std::make_unique< HB >( 123 ) );
		theHandlerBoard.AttachHandler_4_Event( TEventHandlers::EEvent::kReset, std::make_unique< HA >( "Reset 1" ) );


		theHandlerBoard.AttachHandler_4_Event( TEventHandlers::EEvent::kExternal, std::make_unique< HB >( 100 ) );
		theHandlerBoard.AttachHandler_4_Event( TEventHandlers::EEvent::kExternal, std::make_unique< HB >( 200 ) );


		theHandlerBoard();		// Uruchom wszystko

	}







}


// --------------------------------------------------------
