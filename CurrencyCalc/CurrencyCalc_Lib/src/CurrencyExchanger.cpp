


#include "CurrencyExchanger.h"
#include <algorithm>




namespace CppBook
{

using std::wostream, std::wistream;	// Wprowadź te obiekty std do zakresu


wostream & operator << ( wostream & o, const TCurrencyExchanger & c )
{
	for( const auto & currency : c.fCurrencyMap )
		o << currency.second << L"\n";
	return o;
}

wistream & operator >> ( wistream & i, TCurrencyExchanger & c )
{
	TCurrency	currency;		// tymczasowa waluta (jeden wiersz z pliku)

	// Czytaj rekord po rekordzie i wstawiaj do mapy.
	// fCurrKey staje się kluczem mapy.
	while( i >> currency )
		c.AddCurrency( currency );

	return i;
}
// Ta funkcja konwertuje wartość w jednej walucie na wartość w innej walucie
bool TCurrencyExchanger::Convert( const wstring & from_key, const double from_val, const wstring & to_key, double & to_val ) const
{
	try
	{
		// Pobierz kursy wymiany 
		double fromCurr_ExchRatio	= fCurrencyMap.at( from_key ).GetSellRate();
		double toCurr_ExchRatio		= fCurrencyMap.at( to_key ).GetBuyRate();

		// Najpierw kupujemy dla odniesienia
		double val = from_val * fromCurr_ExchRatio;
	
		// Następnie sprzedajemy
		assert( toCurr_ExchRatio > 1e-6 );	// sprawdź, czy nie dzielimy przez 0
		to_val = val / toCurr_ExchRatio;
	}
	catch( ... )
	{
		return false;		// problemy, przykro mi

	}
		
	return true;			// operacja zakończona sukcesem
}

// Znajdź i zwróć walutę na podstawie jej kodu.
// Zwraca true, jeśli ok, lub false, gdy nie można znaleźć.
bool TCurrencyExchanger::FindCurrency( const wstring & currency_code, TCurrency & outCurrency ) const
{       // Nowa funkcjonalność w C++17
	if( auto pos = fCurrencyMap.find( currency_code ); pos != fCurrencyMap.end() )
	{
		outCurrency = ( * pos ).second;
		return true;
	}
		
	return false;
}


void TCurrencyExchanger::AddCurrency( const TCurrency & new_currency )
{
	fCurrencyMap[ new_currency.GetCurrKey() ] = new_currency;	
}




}	// Koniec przestrzeni nazw CppBook



