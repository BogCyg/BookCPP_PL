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



// Idiom preprocesora aby do³¹czaæ ten plik hederowy wy³¹cznie raz
#ifndef QuadEq_h
#define QuadEq_h


#include <iostream>
#include <cassert>



///////////////////////////////////////////////////////////
//  Ta klasa implementuje równanie kwadratowe w postaci:
//
//		a*x*x + b*x + c = 0
//
///////////////////////////////////////////////////////////
class TQuadEq
{
	private:

		double fa {}, fb {}, fc {};	// wspó³czynniki równania

	public:

		// ===================================================
		
		// konstruktor domyœlny klasy
		TQuadEq( void ) : fa( 0.0 ), fb( 0.0 ), fc( 0.0 )
		{}
		
		 // konstruktor parametryczny klasy
		TQuadEq( double a, double b, double c )
			: fa( a ), fb( b ), fc( c )
		{}
	

		// ===================================================


	public:

		// Gettery i settery
		double Get_a( void ) const { return fa; }
		double Get_b( void ) const { return fb; }
		double Get_c( void ) const { return fc; }


		void Set_a( double a ) { fa = a; }
		void Set_b( double b ) { fb = b; }
		void Set_c( double c ) { fc = c; }

	public:

		// Funkcje pomocnicze do obliczania wyró¿nika równania kwadratowego.
		// Jest to funkcja inline (definicja funkcji znajduje siê w klasie)
		double ComputeDelta( void ) const { return fb * fb - 4.0 * fa * fc; }

		 // Zdefiniuj pewne sta³e dla klasy – za pomoc¹ silnego typu wyliczeniowego
		enum class EEqType { kNone, kOne, kTwo, kLinOne, kLinContra };


		///////////////////////////////////////////////////////////
		// Ta funkcja sprawdza typ równania 
		///////////////////////////////////////////////////////////
		//		
		// WEJŒCIE:
		//			delta
		//		
		// WYJŒCIE:
		//			Dok³adny typ równania 
		//				reprezentowanego przez parametry fa, fb, fc
		//		
		// UWAGI:
		//			Rozdzielenie analizy problemu
		//			od rozwi¹zania problemu
		//	
		virtual EEqType GetNumOfRoots( const double delta ) const;


		///////////////////////////////////////////////////////////
		// Ta funkcja oblicza pierwiastki równania,
		// jeœli istniej¹.
		///////////////////////////////////////////////////////////
		//		
		// WEJŒCIE:
		//			theRoot_1 - referencja do obiektu, który
		//				awiera root_1, gdy zwrócono kLinOne, kOne lub kTwo
		//			theRoot_2 - referencja do obiektu, który
		//				zawiera root_2, gdy zwrócono kOne lub kTwo
		//				(w pierwszym przypadku root_1 == root_2)
		//		
		// WYJŒCIE:
		//			status równania (liczba pierwiastków)
		//		
		// UWAGI:
		//			Wartoœci, do których odnosz¹ siê theRoot_1 i theRoot_2
		//			s¹ niezdefiniowane we wszystkich innych przypadkach ni¿ te powy¿ej.
		//
		//	
		EEqType GetRoots( double & theRoot_1, double & theRoot_2 ) const;

};



//////////////////////////////////////////////////////////
// Operacje wejœcia/wyjœcia (zwykle funkcje zewnêtrzne)
std::ostream & operator << ( std::ostream & o, const TQuadEq & equation );
std::istream & operator >> ( std::istream & i, TQuadEq & equation );





#endif // QuadEq_h










