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



// Dołączmy definicję klasy TComplex
#include "Complex.h"



namespace CppBook
{


	// Używane do sprawdzania potencjalnego dzielenia przez 0
	const double kDivThresh { 1e-36 };


	///////////////////////////////////////////////////////////
	// Przeciążone operatory arytmetyczne dla klasy TComplex
	///////////////////////////////////////////////////////////

	// +
	TComplex TComplex::operator + ( const TComplex & second_op ) const
	{
		TComplex retComplex( fRe + second_op.fRe, fIm + second_op.fIm );
		return retComplex;		// Zwróć obiekt przez wartość
	}

	TComplex & TComplex::operator += ( const TComplex & second_op )
	{
		fRe += second_op.fRe, fIm += second_op.fIm;
		return * this;			// Zwróć obiekt przez referencję
	}



	// -
	TComplex TComplex::operator - ( const TComplex & second_op ) const
	{
		TComplex retComplex( fRe - second_op.fRe, fIm - second_op.fIm );
		return retComplex;
	}

	TComplex & TComplex::operator -= ( const TComplex & second_op )
	{
		fRe -= second_op.fRe, fIm -= second_op.fIm;
		return * this;
	}


	// *
	TComplex TComplex::operator * ( const TComplex & second_op ) const
	{
		TComplex retComplex( fRe * second_op.fRe - fIm * second_op.fIm, fRe * second_op.fIm + fIm * second_op.fRe );
		return retComplex;
	}

	TComplex & TComplex::operator *= ( const TComplex & second_op )
	{
		fRe = fRe * second_op.fRe - fIm * second_op.fIm;
		fIm = fRe * second_op.fIm + fIm * second_op.fRe;
		return * this;
	}


	// dzielenie – może zgłosić wyjątek dzielenia przez zero
	TComplex TComplex::operator / ( const TComplex & second_op ) const
	{
		auto div = second_op.fRe * second_op.fRe + second_op.fIm * second_op.fIm;
		if( fabs( div ) < kDivThresh )	// nie dziel przez małą liczbę lub 0
			throw std::overflow_error( "div by 0 error" );	// lepsze niż sprawdzenie tylko div==0.0

		auto re = fRe * second_op.fRe + fIm * second_op.fIm;
		re /= div;

		auto im = fIm * second_op.fRe - fRe * second_op.fIm;
		im /= div;

		return TComplex( re, im );		// Zwróć obiekt przez wartość
	}

	TComplex & TComplex::operator /= ( const TComplex & second_op )
	{
		auto div = second_op.fRe * second_op.fRe + second_op.fIm * second_op.fIm;
		if( fabs( div ) < kDivThresh )
			throw std::overflow_error( "div by 0 error" );

		auto re = fRe * second_op.fRe + fIm * second_op.fIm;
		re /= div;

		auto im = fIm * second_op.fRe - fRe * second_op.fIm;
		im /= div;

		// Copy the values
		fRe = re;
		fIm = im;

		return * this;		// Zwróć obiekt przez referencję
	}



	/////////////////////////////////////////////////////////
	// Operatory strumieniowania – nie muszą być deklarowane
	// jako zaprzyjaźnione (friend)

	std::istream & operator >> ( std::istream & i, TComplex & complex )
	{
		double re {}, im {};
		i >> re;
		i >> im;
		complex.SetRe( re );
		complex.SetIm( im );
		return i;
	}

	std::ostream & operator << ( std::ostream & o, const TComplex & complex )
	{
		o << complex.GetRe() << " " << complex.GetIm();
		return o;
	}

	/////////////////////////////////////////////////////////

	double abs( const TComplex & c )
	{
		return std::sqrt( c.GetIm() * c.GetIm() + c.GetRe() * c.GetRe() );
	}


}		// koniec przestrzeni nazw CppBook

/////////////////////////////////////////////////////////



