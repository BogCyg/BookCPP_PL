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



// Ścieżki względem pozycji  
// plików projektu
#include "../../Complex/include/Complex.h"
#include "../../QuadEq/include/QuadEq.h"


using	CppBook::TComplex;


class TComplexQuadEq : public TQuadEq
{
	public:

		// Wprowadź EEqType z klasy bazowej
		using TQuadEq::EEqType;

	public:

		// ===================================================
		
		// class default constructor
		TComplexQuadEq( void )
		{}
		
		// Konstruktor domyślny klasy
		TComplexQuadEq( double a, double b, double c )
			: TQuadEq( a, b, c )		// Wywołaj konstruktor klasy bazowej
		{}

		// Domyślny konstruktor kopiujący klasy
		TComplexQuadEq( const TComplexQuadEq & ) = default;

		// Domyślny destruktor klasy
		~TComplexQuadEq() = default;
													
		// ===================================================

	public:

		///////////////////////////////////////////////////////////
		// Ta funkcja sprawdza typ równania
		///////////////////////////////////////////////////////////
		//		
		// WEJŚCIE: 		delta
		// WYJŚCIE:		Dokładny typ równania 
		//				rreprezentowanego przez parametry f_a, f_b, f_c
		//		
		EEqType GetNumOfRoots( const double delta ) const;


		///////////////////////////////////////////////////////////
		// Ta funkcja oblicza pierwiastki równania, jeśli istnieją.
		///////////////////////////////////////////////////////////
		//		
		//	WEJŚCIE:	theRoot_1 - referencja do obiektu, który zawiera
		//				pierwiastek 1, jeśli zwrócono kLinOne, kOne lub kTwo
		//				theRoot_2 - referencja do obiektu, który zawiera
		//				pierwiastek 2, jeśli zwrócono kOne lub kTwo
		//				(w pierwszym przypadku root_1 == root_2)
		//		
		// WYJŚCIE: stan równania (liczba pierwiastków)
		//		
		//	UWAGI:	Wartości, do których odwołują się theRoot_1 i theRoot_2
		//				są niezdefiniowane we wszystkich innych przypadkach niż powyższe.
		//		
		EEqType GetRoots( TComplex & theRoot_1, TComplex & theRoot_2 ) const;

};


