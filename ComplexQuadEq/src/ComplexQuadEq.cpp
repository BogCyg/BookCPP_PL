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




#include "ComplexQuadEq.h"



///////////////////////////////////////////////////////////
// This function checks type of the equation 
///////////////////////////////////////////////////////////
//		
// INPUT: 		delta
// OUTPUT:		An exact type of the equation 
//				represented by the parameters f_a, f_b, f_c
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
// This function computes the roots of the equation, if possible.
///////////////////////////////////////////////////////////
//		
//	INPUT:	theRoot_1 - a reference to an object which
//				contains root 1 if returned kLinOne, kOne or kTwo
//				theRoot_2 - a reference to an object which
//				contains root 2 if returned kOne or kTwo
//				(in the first case root_1 == root_2)
//		
// OUTPUT: status of the equation (number of roots)
//		
//	REMARKS:	The values referenced to by theRoot_1 and theRoot_2
//				are undefined in all other cases than stated above.
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


