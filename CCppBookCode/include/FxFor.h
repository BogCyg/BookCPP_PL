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



#pragma once


#include <iostream>
#include <iomanip>
#include <cassert>
#include <limits>







///////////////////////////////////////////////////////////
// Klasa do reprezentacji liczb stałoprzecinkowych. 
// Brak saturacji, brak kontroli przepełnienia.
// SupportType ‐ definiuje typ całkowity BEZ ZNAKU dla całej liczby
// Prec ‐ definiuje liczbę bitów ułamkowych
// ACC_TYPE - Typ akumulatora (dla wyników pośrednich)
///////////////////////////////////////////////////////////
template< typename ST, int Prec, typename ACC_TYPE = unsigned long long >
//template< typename ST, typename ST Prec, typename ACC_TYPE = unsigned long long >
class FxFor
{
private:

	// Przechowuje całą liczbę
	ST	fValue {};

public:

	// Zwraca wewnętrzną reprezentację w formacie ZM (znak/moduł)
	constexpr ST GetInternalValue( void ) const 
		{ return fValue; }		

	// Zwraca wewnętrzną reprezentacją w formacie U2
	constexpr ST GetInternalValue_in_C2( void ) const 
		{ return IsPositive() ? fValue : ( ~fValue | kSignMask ) + 1; }

	constexpr void SetInternalValue( ST new_val ) 	
		{ fValue = new_val; }


public:
	
	// Lokalna stała dla precyzji
	enum : ST	{ kPrec = Prec };

private:

	// Zdefiniujmy pewne przydatne flagi
	enum : ST	{	
				kSignMask	= ST(1) << ( 8 * sizeof( ST ) - 1 ),		// bit znaku (całkowity najbardziej znaczący bit)
				kIntegerLSB = ST(1) << kPrec,							// najmniej znaczący bit części całkowitej
				kFractMSB	= kPrec > 0 ? ST(1) << kPrec - ST(1) : 0	// najbardziej znaczący bit części ułamkowej
			};


	// Skrót do tego typu
	using FxType = FxFor< ST, Prec, ACC_TYPE >;

public:

	// Pewne manipulatory danych surowych
	constexpr ST DataValueAbs( void ) const { return fValue & ~kSignMask; }	// Zwróć wartość bezwzględną (zawsze dodatnia)
																		 
	constexpr ST GetMagnitudeOfIntegerPart( void ) const 
		{ return DataValueAbs() >> kPrec; }

	constexpr ST GetFractionalPart( void ) const { return fValue & ( kIntegerLSB - 1 ); } 
								    // ( kIntegerLSB ‐ 1 ) ustawia wszystkie bity części ułamkowej
public:

	// ===================================================
	// Domyślny konstruktor klasy
	constexpr FxFor( void ) : fValue( 0 ) 					
	{
		static_assert( sizeof( ST ) * 8 > kPrec );
		//static_assert( fValue >= 0 );		nie skompiluje się, bo fValue nie jest znana
		assert( sizeof( ST ) * 8 > kPrec );
	}

	// Konstruktory konwersji typu
	constexpr FxFor( int x )
	{
		assert( sizeof( ST ) * 8 > kPrec );
		fValue = x < 0 ? - x << kPrec | kSignMask : x << kPrec;
	}

	constexpr FxFor( char x )
	{
		assert( sizeof( ST ) * 8 > kPrec );
		fValue = x < 0 ? - x << kPrec | kSignMask : x << kPrec;
	}

	constexpr FxFor( short x )
	{
		assert( sizeof( ST ) * 8 > kPrec );
		fValue = x < 0 ? - x << kPrec | kSignMask : x << kPrec;
	}

	constexpr FxFor( long x )
	{
		assert( sizeof( ST ) * 8 > kPrec );
		fValue = x < 0 ? - x << kPrec | kSignMask : x << kPrec;
	}


	constexpr FxFor( double x );							// konstruktor klasy


	template< typename D, int P, typename A >
	constexpr FxFor( const FxFor< D, P, A > & f )			// mieszany konstruktor kopiujący
	{
		// Najpierw skopiuj część całkowitą, aby nie stracić najbardziej znaczącego bitu
		fValue = f.GetMagnitudeOfIntegerPart() << kPrec;
		// Następnie skopiuj najbardziej znaczącą część części ułamkowej
		fValue |= f.kPrec > kPrec ? f.GetFractionalPart() >> f.kPrec - kPrec 
									: f.GetFractionalPart() << kPrec - f.kPrec;
		// Na koniec ustaw znak
		if( f.IsNegative() )
			MakeNegative();
	}

	// ===================================================

	template< class D, int P, typename A >
	constexpr FxType & operator = ( const FxFor< D, P, A > & f )	// mieszane przypisanie
	{
		// Dla różnych typów może powodować utratę danych
		if( (void*)& f != (void*)this )		// ochrona przed samoprzypisaniem
		{
			// Najpierw skopiuj część całkowitą, aby nie stracić najbardziej znaczącego bitu
			fValue = f.GetMagnitudeOfIntegerPart() << kPrec;
			// Następnie skopiuj najbardziej znaczący fragment części ułamkowej
			fValue |= f.kPrec > kPrec ? f.GetFractionalPart() >> f.kPrec - kPrec 
										: f.GetFractionalPart() << kPrec - f.kPrec;
			// Na koniec ustaw znak
			if( f.IsNegative() )
				MakeNegative();
		}

		return * this;
	}



	// Operatory konwersji:

	constexpr operator char()			const;
	constexpr operator short()			const;
	constexpr operator int()			const;
	constexpr operator long()			const;

	constexpr operator double()			const;

	// ===================================================
	// Funkcje pomocnicze:

	constexpr bool IsNegative( void ) const 
		{ return ( fValue & kSignMask ) == 0 ? false : true; }
	constexpr bool IsPositive( void ) const 
		{ return ( fValue & kSignMask ) != 0 ? false : true; }		// 0 również jest dodatnie
	 
	constexpr void ChangeSign( void ) { fValue ^= kSignMask; }		

	constexpr void MakeNegative( void ) 
		{ assert( fValue != 0 ); fValue |= kSignMask; }				// Włącz bit znaku

	constexpr void MakePositive( void ) { fValue &= ~kSignMask; }	// Wyłącz znak

	constexpr void MakeAbs( void ) { MakePositive(); }				// Pozbądź się znaku

	constexpr FxType GetAbs( void ) const 
		{ FxType tmp( * this ); tmp.MakeAbs(); return tmp; }		// Zwróć wartość bezwzględną


	// ===================================================
	// Podstawowa biblioteka działań:

	constexpr FxType operator + ( FxType f ) const;
	constexpr FxType operator - ( FxType f ) const;
	constexpr FxType operator * ( FxType f ) const;
	constexpr FxType operator / ( FxType f ) const;
	 
	constexpr FxType & operator += ( FxType f );	
	constexpr FxType & operator -= ( FxType f );
	constexpr FxType & operator *= ( FxType f );
	constexpr FxType & operator /= ( FxType f );
	 
	constexpr FxType & operator - ( void );		

	// ===================================================

	constexpr FxType operator & ( FxType f ) const;
	constexpr FxType operator | ( FxType f ) const;
	constexpr FxType operator ^ ( FxType f ) const;
	 
	constexpr FxType & operator &= ( FxType f );
	constexpr FxType & operator |= ( FxType f );
	constexpr FxType & operator ^= ( FxType f );
	 
	constexpr FxType & operator ~ ( void );

	// ===================================================

	constexpr FxType operator ++ ( int );	// przyrostkowa
	constexpr FxType & operator ++ ();		// przedrostkowa
	 
	constexpr FxType operator -- ( int );	// przyrostkowa
	constexpr FxType & operator -- ();		// przedrostkowa
	 
	// ===================================================
	 
	constexpr FxType operator << ( int shift ) const;
	constexpr FxType operator >> ( int shift ) const;
	 
	constexpr FxType & operator <<= ( int shift );
	constexpr FxType & operator >>= ( int shift );

	// ===================================================
	// Operatory porównywania:

	constexpr bool operator ==	( FxType f ) const;
	constexpr bool operator !=	( FxType f ) const;
	constexpr bool operator <	( FxType f ) const;
	constexpr bool operator <=	( FxType f ) const;
	constexpr bool operator >	( FxType f ) const;
	constexpr bool operator >=	( FxType f ) const;

	// ===================================================

};

///////////////////////////////////////////////////////////







// ===================================================
// Konstruktor konwersji typu: zmiennoprzecinkowy na stałoprzecinkowy
//template< typename ST, int Prec, typename ACC_TYPE >
template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::FxFor( double x ) : fValue( 0 )
{			
	bool minus_sign { false };
	if( x < 0.0 )
	{
		minus_sign = true;		// pamiętaj znak,
		x = -x;					// astępnie weź wartość bezwzględną
	}


	ST int_part = static_cast< ST >( x );	// tutaj używamy konwersji standardowej
						// z double, która przycina ułamek

	fValue = int_part;
	fValue <<= kPrec;		// umieść część całkowitą na swoim miejscu

	double fract_part = x - int_part;

	double scaled_fraction = fract_part * static_cast< double >( kIntegerLSB );
	ST fraction = static_cast< ST >( scaled_fraction );

	fValue |= fraction;			// połącz dwie wartości

	if( minus_sign == true && fValue != 0 )		
		MakeNegative();			// na koniec weź pod uwagę znak

}			




// Powtarzamy ten sam kod, co dla konwersji "double", w celu uniknięcia
// niejawnej konwersji z "float" na "double", gdy używane są 
// dodatkowe funkcje.
template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::operator double() const
{ 
	// Zacznij od ułamka
	double retVal = static_cast< double >( GetFractionalPart() ) / static_cast< double >( kIntegerLSB );

	retVal += GetMagnitudeOfIntegerPart();	// teraz dodaj część całkowitą
	return IsNegative() ? - retVal : retVal;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::operator char() const
{ 
	constexpr char kMaxOutMagnitude { std::numeric_limits< char >::max() };
	// The fractionalRemainder takes on 1 if the fractional part is greater or equal to 0.5
	// and the magnitude value is less than the maximum for the output type (otherwise
	// there would be an overflow in the output value);
	assert( GetMagnitudeOfIntegerPart() <= kMaxOutMagnitude );		// otherwise we'll have an overflow in this conversion
	ST fractionalRemainder = ( fValue & kFractMSB ) == 0 || GetMagnitudeOfIntegerPart() >= kMaxOutMagnitude ? ST(0) : ST(1);
	char out_val { static_cast< char >( GetMagnitudeOfIntegerPart() + fractionalRemainder ) };
	return IsPositive() ? out_val : - out_val;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::operator short() const
{ 
	constexpr short kMaxOutMagnitude { std::numeric_limits< short >::max() };
	// The fractionalRemainder takes on 1 if the fractional part is greater or equal to 0.5
	// and the magnitude value is less than the maximum for the output type (otherwise
	// there would be an overflow in the output value)
	assert( GetMagnitudeOfIntegerPart() <= kMaxOutMagnitude );		// otherwise we'll have an overflow in this conversion
	ST fractionalRemainder = ( fValue & kFractMSB ) == 0 || GetMagnitudeOfIntegerPart() >= kMaxOutMagnitude ? ST(0) : ST(1);
	short out_val { static_cast< short >( GetMagnitudeOfIntegerPart() + fractionalRemainder ) };
	return IsPositive() ? out_val : - out_val;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::operator int() const
{ 
	constexpr int kMaxOutMagnitude { std::numeric_limits< int >::max() };
	// The fractionalRemainder takes on 1 if the fractional part is greater or equal to 0.5
	// and the magnitude value is less than the maximum for the output type (otherwise
	// there would be an overflow in the output value)
	assert( GetMagnitudeOfIntegerPart() <= kMaxOutMagnitude );		// otherwise we'll have an overflow in this conversion
	ST fractionalRemainder = ( fValue & kFractMSB ) == 0 || GetMagnitudeOfIntegerPart() >= kMaxOutMagnitude ? ST(0) : ST(1);
	int out_val { static_cast< int >( GetMagnitudeOfIntegerPart() + fractionalRemainder ) };
	return IsPositive() ? out_val : - out_val;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr FxFor< ST, Prec, ACC_TYPE >::operator long() const
{ 
	constexpr long kMaxOutMagnitude { std::numeric_limits< long >::max() };
	// The fractionalRemainder takes on 1 if the fractional part is greater or equal to 0.5
	// and the magnitude value is less than the maximum for the output type (otherwise
	// there would be an overflow in the output value)
	assert( GetMagnitudeOfIntegerPart() <= kMaxOutMagnitude );		// otherwise we'll have an overflow in this conversion
	ST fractionalRemainder = ( fValue & kFractMSB ) == 0 || GetMagnitudeOfIntegerPart() >= kMaxOutMagnitude ? ST(0) : ST(1);
	long out_val { static_cast< long >( GetMagnitudeOfIntegerPart() + fractionalRemainder ) };
	return IsPositive() ? out_val : - out_val;
}


// ===================================================

// przedrostkowa
template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator ++ ()
{
	* this += 1;
	return * this;
}
template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator -- ()
{
	* this -= 1;
	return * this;
}

// przyrostkowa
template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator ++ ( int )
{
	FxType tmp( * this );	// to niestety wymaga tymczasowej kopii
	* this += 1;
	return tmp;
}
template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator -- ( int )
{
	FxType tmp( * this );	// to niestety wymaga tymczasowej kopii
	* this -= 1;
	return tmp;
}



// ===================================================

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator + ( FxType f ) const
{
	FxType tmp( * this );
	return tmp += f;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator - ( FxType f ) const
{
	f.ChangeSign();
	return operator + ( f );
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator * ( FxType f ) const
{
	FxType tmp( * this );
	return tmp *= f;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator / ( FxType f ) const
{
	FxType tmp( * this );
	return tmp /= f;
}


// ===================================================

//
// C++ standard stands that: The RIGHT shift is quaranteed to be logical (0-fill)
// if the shifted value has an unsigned type or if it has a nonnegative value;
// otherwise the result is implementation dependent.
// The LEFT (...) vacated bits are 0-filled.
//
template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator <<= ( int shift )
{
	IsPositive() ? fValue <<= shift : fValue <<= shift, MakeNegative();
	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator >>= ( int shift )
{
	IsPositive() ? fValue >>= shift : ( fValue &= ~kSignMask ) >>= shift, MakeNegative();
	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator << ( int shift ) const
{
	FxType tmp( * this );
	tmp.fValue <<= shift;
	return tmp;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator >> ( int shift ) const
{
	FxType tmp( * this );
	tmp.fValue >>= shift;
	return tmp;
}

// ===================================================

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator += ( FxType f )
{
	// Wykonujemy arytmetykę znak-moduł
	bool first_is_negative	= IsNegative();
	bool second_is_negative = f.IsNegative();

	if( first_is_negative )
	{
		if( second_is_negative )
		{
			// Obie są ujemne

			MakeAbs();				// Weź wartość bezwzględną pierwszego operandu
			f.MakeAbs();			// Weź wartość bezwzględną drugiego operandu


			fValue += f.fValue;		// Dodaj same moduły;


			MakeNegative();			// Odwróć znak wyniku
		}
		else
		{
			// Pierwsza jest ujemna, druga jest dodatnia

			MakeAbs();	// po prostu wykonuj na module (nie zwracając uwagi na bit znaku)

			// Tutaj porównujemy tylko moduły; Pierwsza jest dodatnia, więc nie trzeba pobierać wartość bezwzględnej
			if( fValue <= f.fValue )		// słaba nierówność, aby 0 było dodatnie		
			{
				fValue = f.fValue - fValue;	// i NIE zmieniamy znaku
			}
			else
			{
				fValue -= f.fValue;
				assert( IsPositive() );
				if( fValue != 0 )
					MakeNegative();					// odwracamy znak wyniku
			}
		}
	}
	else
	{
		if( second_is_negative )
		{
			// Pierwsza jest dodatnia, druga jest ujemna

			f.MakeAbs();	// po prostu wykonuj na module (nie zwracając uwagi na bit znaku)

			// Tutaj porównujemy tylko moduły;
			// Pierwsza jest dodatnia, więc nie trzeba pobierać wartość bezwzględnej
			if( fValue >= f.fValue )	// słaba nierówność, aby 0 było dodatnie	
			{
				fValue -= f.fValue;		// i NIE zmieniamy znaku
			}
			else
			{
				fValue = f.fValue - fValue;
				assert( IsPositive() );
				if( fValue != 0 )
					MakeNegative();			// i odwracamy znak wyniku
			}
		}
		else
		{
			// Obie są dodatnie

			fValue += f.fValue;
		}
	}

	return * this;
}


template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator -= ( FxType f )
{
	f.ChangeSign();
	return operator += ( f );
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator *= ( FxType f )
{
	// Wykonujemy arytmetykę znak-moduł
	bool first_is_negative	= IsNegative();
	bool second_is_negative = f.IsNegative();

	// Potrzebny nam jest wystarczająco długi akumulator do przechowania rezultatu.
	ACC_TYPE theAccumulator = DataValueAbs();		
	// Wczytujemy tu wartość bezwzględną, która zostaje przesunięta, np. jeśli 
	// wczytamy stałoprzecinkową 1.0, wartość ta w akumulatorze NIE jest jednostką,
	// lecz wartością przesuniętą w lewo o kPrec
	assert( sizeof( theAccumulator ) >= 2 * sizeof( ST ) );

	theAccumulator *= f.DataValueAbs();		// pomnóż DODATNIE moduły 
	
	// Teraz musimy przesunąć wynik w prawo o kPrec,
	// aby uciąć kPrec najmniej znaczących bitów (zostaną utracone!).
	// Pozostałość dobrze pasuje do formatu stałoprzecinkowego: int.frac
	theAccumulator >>= kPrec;

	// Skopiuj przesunięty akumulator do obiektu zwracanego
	fValue = static_cast< ST >( theAccumulator );

	// Na koniec ustaw znak wyniku
	if( ( first_is_negative ^ second_is_negative ) && fValue != 0 )
		MakeNegative();

	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator /= ( FxType f )
{
	if( f.fValue == 0 )
	{
		return * this;							// error, trying to divide by zero! (set an error flag?)
	}

	// We perform the sign-magnitude arithmetic
	bool first_is_negative	= IsNegative();
	bool second_is_negative = f.IsNegative();

	// First we need an accumulator that is long enough to store the result.
	ACC_TYPE theAccumulator = DataValueAbs();	// a divident goes here
	assert( sizeof( theAccumulator ) >= 2 * sizeof( ST ) );


	theAccumulator <<= kPrec;					// we need to shift the first operand
												// to accomodate for the integer division used 
												// in the next statement

	theAccumulator /= f.DataValueAbs();			// divide the magnitudes- we employ here the available
												// standard division of the POSITIVE integers

	fValue = static_cast< ST >( theAccumulator );	// copy back the result

												// Finally set the sign of the result
	if( ( first_is_negative ^ second_is_negative ) && fValue != 0 )
		MakeNegative();

	return * this;
}


template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator - ( void )
{
	ChangeSign();
	return * this;
}


///////////////////////////////////////////////////////////
// Logical operators:


template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator & ( FxType f ) const
{
	FxType tmp( * this );
	return tmp &= f;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator | ( FxType f ) const
{
	FxType tmp( * this );
	return tmp |= f;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType FxFor< ST, Prec, ACC_TYPE >::operator ^ ( FxType f ) const
{
	FxType tmp( * this );
	return tmp ^= f;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator ~ ( void )
{
	fValue = ~ fValue;
	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator &= ( FxType f )
{
	fValue &= f.fValue;
	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator |= ( FxType f )
{
	fValue |= f.fValue;
	return * this;
}

template< typename ST, int Prec, typename ACC_TYPE >
constexpr typename FxFor< ST, Prec, ACC_TYPE >::FxType & FxFor< ST, Prec, ACC_TYPE >::operator ^= ( FxType f )
{
	fValue ^= f.fValue;
	return * this;
}






///////////////////////////////////////////////////////////
// Comparison operators:

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator == ( FxType f ) const
{
	assert( DataValueAbs() != 0 || IsPositive() );
	assert( f.DataValueAbs() != 0 || f.IsPositive() );
	return fValue == f.fValue;
}

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator != ( FxType f ) const
{
	return ! operator == ( f );
}

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator < ( FxType f ) const
{
	assert( DataValueAbs() != 0 || IsPositive() );
	assert( f.DataValueAbs() != 0 || f.IsPositive() );
	if( IsNegative() == true )														// we compare ABS only if the same sign
		return f.IsNegative() == true ? DataValueAbs() > f.DataValueAbs() : true;	// an opposite condition if both negative
	else
		return f.IsNegative() == true ? false : DataValueAbs() < f.DataValueAbs();
}

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator <= ( FxType f ) const
{
	return operator < ( f ) || operator == ( f );
}

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator > ( FxType f ) const
{
	return ! operator <= ( f );
}

template< typename ST, int Prec, typename ACC_TYPE >
bool constexpr FxFor< ST, Prec, ACC_TYPE >::operator >= ( FxType f ) const
{
	return ! operator < ( f );
}

///////////////////////////////////////////////////////////

template< typename D, int P, typename A >
auto & operator << ( std::ostream & o, const FxFor< D, P, A > & f )
{
	o << f.GetInternalValue();
	return o;
}

template< typename D, int P, typename A >
auto & operator >> ( const std::istream & i, FxFor< D, P, A > & f )
{
	typename FxFor< D, P >::ST d;
	i >> d;
	f.SetInternalValue( d );
	return i;
}


///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
// Ta funkcja zwraca różnicę w reprezentacjach
// między double i FxFor<>
///////////////////////////////////////////////////////////
//		
// WEJŚCIE:
//			d - wartość wejściowa double
//			f - FxFor<> do sprawdzenia
//		
// WYJŚCIE:
//			różnica (jako wartość double) między double
//			i reprezentacją stałoprzecinkową tej liczby
//		
// UWAGI:
//		
//		
template< typename D, int P, typename A >
constexpr auto ComputeRoundingError( const double d, const FxFor< D, P, A > f )
{
	auto diff( d - static_cast< double >( f ) );
	return diff < 0.0 ? - diff: diff;		// std::fabs nie jest przyjazna constexpr
}

template< typename D, int P, typename A >
constexpr auto ComputeRoundingError( const FxFor< D, P, A > f, const double d )
{
	auto diff( d - static_cast< double >( f ) );
	return diff < 0.0 ? - diff: diff;	
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

// Definiujemy tu konkretne typy danych. Postępuj ostrożnie
// i sprawdź rozmiary typów wbudowanych na swoim komputerze!

using FX_8_8	= FxFor< unsigned short, 8  >;
using FX_16_16	= FxFor< unsigned int,	16 >;
using FX_24_8	= FxFor< unsigned int,	8 >;
using FX_8_24	= FxFor< unsigned int,	24 >;

// Poniższe typy są znormalizowanymi liczbami,
// dla których ich moduł jest mniejszy niż 1.0.
using FX_PURE_FRACT_15 = FxFor< unsigned short,	15 >;
using FX_PURE_FRACT_31 = FxFor< unsigned int,	31 >;





///////////////////////////////////////////////////////////







