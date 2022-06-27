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


#pragma once		// dołącz ten nagłówek tylko raz w jednostce translacji

#include <iostream>
#include <string>
#include <cassert>




namespace CppBook
{
	

using std::wstring;


class TCurrency
{
	private:

		wstring		fCurrKey;		// 3-literowy kod, taki jak USD, EUR, PLN
		wstring		fCurrName;		// unikatowa nazwa waluty do wyświetleniad

		double		fSellRate {};		// kurs sprzedaży – zawsze dodawaj {} do standardowych typó
		double		fBuyRate {};		// kurs kupna

	public:

		// Dwa konstruktory w jednym (domyślny i parametryczny)
		TCurrency(	const wstring & currCode = L"", const wstring & currName = L"", 
					const double sellRate = 0.0, const double buyRate = 0.0 )
			: fCurrKey( currCode ), fCurrName( currName ), fSellRate( sellRate ), fBuyRate( buyRate )
		{}

	public:

		// Funkcje do odczytywania danych
		wstring		GetCurrKey( void ) const { return fCurrKey; }
		wstring		GetCurrName( void ) const { return fCurrName; }	

		double		GetSellRate( void ) const { return fSellRate; }			
		double		GetBuyRate( void ) const { return fBuyRate; }			


		// Funkcje do zapisywania danych
		void		SetCurrCode( const wstring & s ) { fCurrKey = s; }
		void		SetCurrName( const wstring & s ) { fCurrName = s; }	
					
		void		SetSellRate( double r ) { fSellRate = r; }			
		void		SetBuyRate( double r ) { fBuyRate = r; }			
};

// "w" dla strumieni ze znakami dwubajtowymi
std::wostream & operator << ( std::wostream & o, const TCurrency & c );

std::wistream & operator >> ( std::wistream & i, TCurrency & c );


}		// CppBook






