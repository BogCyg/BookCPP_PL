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




#include <cmath>
#include "QuadEq.h"



///////////////////////////////////////////////////////////
// Ta funkcja sprawdza typ równania 
///////////////////////////////////////////////////////////
//		
// WEJŚCIE:
//			delta
//		
// WYJŚCIE:
//			Dokładny typ równania 
//				reprezentowanego przez parametry fa, fb, fc
//		
// UWAGI:
//			Rozdzielenie analizy problemu
//			od rozwiązania problemu
//	
TQuadEq::EEqType TQuadEq::GetNumOfRoots( const double delta ) const
{
	if( fa == 0.0 )
	{
		return fb == 0.0 ? EEqType::kLinContra : EEqType::kLinOne;
	}
	else
	{
		if( delta < 0.0 )
			return EEqType::kNone;
		else
			return delta == 0.0 ? EEqType::kOne : EEqType::kTwo;
	}
}


///////////////////////////////////////////////////////////
// Ta funkcja oblicza pierwiastki równania,
// jeśli istnieją.
///////////////////////////////////////////////////////////
//		
// WEJŚCIE:
//			theRoot_1 - referencja do obiektu, który
//				awiera root_1, gdy zwrócono kLinOne, kOne lub kTwo
//			theRoot_2 - referencja do obiektu, który
//				zawiera root_2, gdy zwrócono kOne lub kTwo
//				(w pierwszym przypadku root_1 == root_2)
//		
// WYJŚCIE:
//			status równania (liczba pierwiastków)
//		
// UWAGI:
//			Wartości, do których odnoszą się theRoot_1 i theRoot_2
//			są niezdefiniowane we wszystkich innych przypadkach niż te powyżej.
//
//	
	
TQuadEq::EEqType TQuadEq::GetRoots( double & root_1, double & root_2 ) const
{
	auto delta( ComputeDelta() );		// wywołaj konstruktor dla typu wbudowanego

	EEqType equationTypeFlag = GetNumOfRoots( delta );

	const double kDivThresh { 1e-36 };		// Używane w assert do weryfikowania dzielenia

	// Dobrym pomysłem jest jawne umieszczenie tu WSZYSTKICH przypadków (dla pewności)
	switch( equationTypeFlag )
	{
		case EEqType::kLinContra:
		case EEqType::kNone:

			break;					// w przypadku równania sprzecznego nic nie rób
		case EEqType::kLinOne:

			assert( fa == 0.0 );
			assert( std::fabs( fb ) > kDivThresh );

			if( std::fabs( fb ) < kDivThresh )
				throw std::overflow_error( "Too low fb" );

			root_1 = root_2 = - fc / fb;

			break;					// zwróć jeden pierwiastek
		
		case EEqType::kOne:
									// tutaj bez przerywania – dla tych dwóch przypadków mamy ten sam kod
		case EEqType::kTwo:

			{	// Potrzebujemy bloku {} dla zmiennych lokalnych

				assert( delta >= 0.0 );	// na wszelki wypadek, kto wie?

				double delta_root = std::sqrt( delta );
				
				double denominator = 2.0 * fa;
				assert( std::fabs( denominator ) > kDivThresh );

				if( std::fabs( denominator ) < kDivThresh )
					throw std::overflow_error( "Too low fa" );

				root_1 = ( - fb - delta_root ) / denominator;
				root_2 = ( - fb + delta_root ) / denominator;
			}

			break;

		default :

			assert( false );		// to nie powinno się zdarzyć – nasz błąd w programowaniu?
			break;
	}

	return equationTypeFlag;
}


//////////////////////////////////////////////////////////
// Operacje wejścia/wyjścia (zwykle funkcje zewnętrzne)
std::ostream & operator << ( std::ostream & o, const TQuadEq & eq )
{
	o << eq.Get_a() << " " << eq.Get_b() << " " << eq.Get_c() << std::endl;
	return o;
}

std::istream & operator >> ( std::istream & i, TQuadEq & eq )
{
	double tmp { 0.0 };
	i >> tmp; eq.Set_a( tmp );
	i >> tmp; eq.Set_b( tmp );
	i >> tmp; eq.Set_c( tmp );
	return i;
}







