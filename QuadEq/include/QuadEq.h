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



// Idiom preprocesora aby do��cza� ten plik hederowy wy��cznie raz
#ifndef QuadEq_h
#define QuadEq_h


#include <iostream>
#include <cassert>



///////////////////////////////////////////////////////////
//  Ta klasa implementuje r�wnanie kwadratowe w postaci:
//
//		a*x*x + b*x + c = 0
//
///////////////////////////////////////////////////////////
class TQuadEq
{
	private:

		double fa {}, fb {}, fc {};	// wsp�czynniki r�wnania

	public:

		// ===================================================
		
		// konstruktor domy�lny klasy
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

		// Funkcje pomocnicze do obliczania wyr�nika r�wnania kwadratowego.
		// Jest to funkcja inline (definicja funkcji znajduje si� w klasie)
		double ComputeDelta( void ) const { return fb * fb - 4.0 * fa * fc; }

		 // Zdefiniuj pewne sta�e dla klasy � za pomoc� silnego typu wyliczeniowego
		enum class EEqType { kNone, kOne, kTwo, kLinOne, kLinContra };


		///////////////////////////////////////////////////////////
		// Ta funkcja sprawdza typ r�wnania 
		///////////////////////////////////////////////////////////
		//		
		// WEJ�CIE:
		//			delta
		//		
		// WYJ�CIE:
		//			Dok�adny typ r�wnania 
		//				reprezentowanego przez parametry fa, fb, fc
		//		
		// UWAGI:
		//			Rozdzielenie analizy problemu
		//			od rozwi�zania problemu
		//	
		virtual EEqType GetNumOfRoots( const double delta ) const;


		///////////////////////////////////////////////////////////
		// Ta funkcja oblicza pierwiastki r�wnania,
		// je�li istniej�.
		///////////////////////////////////////////////////////////
		//		
		// WEJ�CIE:
		//			theRoot_1 - referencja do obiektu, kt�ry
		//				awiera root_1, gdy zwr�cono kLinOne, kOne lub kTwo
		//			theRoot_2 - referencja do obiektu, kt�ry
		//				zawiera root_2, gdy zwr�cono kOne lub kTwo
		//				(w pierwszym przypadku root_1 == root_2)
		//		
		// WYJ�CIE:
		//			status r�wnania (liczba pierwiastk�w)
		//		
		// UWAGI:
		//			Warto�ci, do kt�rych odnosz� si� theRoot_1 i theRoot_2
		//			s� niezdefiniowane we wszystkich innych przypadkach ni� te powy�ej.
		//
		//	
		EEqType GetRoots( double & theRoot_1, double & theRoot_2 ) const;

};



//////////////////////////////////////////////////////////
// Operacje wej�cia/wyj�cia (zwykle funkcje zewn�trzne)
std::ostream & operator << ( std::ostream & o, const TQuadEq & equation );
std::istream & operator >> ( std::istream & i, TQuadEq & equation );





#endif // QuadEq_h










