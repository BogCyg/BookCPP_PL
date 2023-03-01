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



#include <cmath>
#include "ComplexQuadEq.h"




///////////////////////////////////////////////////////////
// Ta funkcja sprawdza typ równania
///////////////////////////////////////////////////////////
//		
// WEJŚCIE: 		delta
// WYJŚCIE:		Dokładny typ równania 
//				rreprezentowanego przez parametry f_a, f_b, f_c
//				
TComplexQuadEq::EEqType TComplexQuadEq::GetNumOfRoots( const double delta ) const
{
	if( Get_a() == 0.0 )
	{
		return Get_b() == 0.0 ? EEqType::kLinContra : EEqType::kLinOne;
	}
	else
	{
		return delta == 0.0 ? EEqType::kOne : EEqType::kTwo;	// W tej klasie znak delty nie jest istotny
	}
}


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
TQuadEq::EEqType TComplexQuadEq::GetRoots( TComplex & root_1, TComplex & root_2 ) const
{
	auto delta( ComputeDelta() );		// Wywołaj konstruktor dla typu wbudowanego

	const auto kDivThresh { 1e-36 };		// Używane w assert do sprawdzania dzielenia

	EEqType equationTypeFlag = GetNumOfRoots( delta );

	// Dobrym pomysłem jest jawne umieszczenie tutaj WSZYSTKICH przypadków (dla pewności)
	switch( equationTypeFlag )
	{
		case EEqType::kNone:

			assert( false );		// nie powinno się zdarzyć
			break;					

		case EEqType::kLinContra:

			break;					// nic nie rób

		case EEqType::kLinOne:

			assert( Get_a() == 0.0 );
			assert( std::fabs( Get_b() ) > kDivThresh );

			if( std::fabs( Get_b() ) < kDivThresh )
				throw std::overflow_error( "Too low Get_b()" );

			root_1 = root_2 = - Get_c() / Get_b();

			break;					// powrót z jednym pierwiastkiem
		
		case EEqType::kOne:			// tutaj bez break – dla tych dwóch przypadków mamy jedno rozwiązanie
		case EEqType::kTwo:

			{	// Potrzebujemy tu bloku {} dla zmiennych lokalnych

				bool negative_delta = delta < 0.0 ? true : false;

				double delta_root = sqrt( negative_delta ? - delta : delta );
				
				double denominator = 2.0 * Get_a();
				assert( std::fabs( denominator ) > kDivThresh );

				if( std::fabs( denominator ) < kDivThresh )
					throw std::overflow_error( "Too low Get_a()" );


				if( negative_delta )
				{
					// Ujemna delta wymaga dziedziny liczb zespolonych
					root_1.SetRe( - Get_b() / denominator );
					root_1.SetIm( - delta_root / denominator );

					root_2.SetRe( - Get_b() / denominator );
					root_2.SetIm(   delta_root / denominator );
				}
				else
				{
					// Dodatnia delta oznacza tylko pierwiastki rzeczywiste
					root_1.SetRe( ( - Get_b() - delta_root ) / denominator );
					root_1.SetIm( 0.0 );

					root_2.SetRe( ( - Get_b() + delta_root ) / denominator );
					root_2.SetIm( 0.0 );
				}

			}

			break;

		default :

			assert( false );		// To nie powinno się zdarzyć – błąd w programowaniu?
			break;
	}

	return equationTypeFlag;
}


