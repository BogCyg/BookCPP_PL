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



#include <string>
#include <vector>
#include <iostream>
#include <tuple>




using namespace std::literals::string_literals;		// aby móc użyć "s w celu zdefiniowania literału typu std::string, jak w "June"s

using std::tuple, std::get, std::tie, std::tuple_size, std::make_tuple, std::ignore;
using std::cout, std::endl;
using std::string;





void tuple_vs_struct( void )
{
	// -----------------------------
	{
		// Przechowajmy datę w krotce
		// dzień miesiąc rok
		tuple< int, string, int >	t_date( 27, "June", 2019 );

		// Łatwiej będzie za pomocą make_tuple
		auto t_date_2 = make_tuple( 27, "June"s, 2019 );	// dzięki s na końcu od razu tworzymy obiekt std::string (a nie const char*)
															// ale pamiętajmy dodać: using namespace std::literals::string_literals
		// uple_size<>::value zwraca liczbę elementów
		cout << "t_date has " << tuple_size< decltype(t_date) >::value 
			<< " elems" << endl;

		// Wypisz elementy – nie zaburzaj porządku 
		cout << "D/M/Y:" << get< 0 >( t_date ) << "/" << 
			get< 1 >( t_date ) << "/" << 
			get< 2 >( t_date ) << endl;

		// Pobierz elementy do osobnych obiektów
		// bez powiązania strukturalnego
		const auto [ d, m, y ] = t_date;	

		// Wypisz elementy 
		cout << "D/M/Y:" << d << "/" << 
			m << "/" << y << endl;

		// Użyj tie z parametrem ignore do pozyskania kilku elementów
		int dd {};
		string mm {};

		// Pobierz tylko dzień i miesiąc, ignorując rok
		tie( dd, mm, ignore ) = t_date;

		// Wypisz elementy 
		cout << "D/M:" << dd << "/" << mm << endl;

	}

	// ------------------------------
	{
		// To samo za pomocą struktury bez nazwy
		struct 
		{
			// Każde pole na swoją nazwę
			int		fDay	{ 27 };
			string	fMonth	{ "June" };
			int		fYear	{ 2019 };
		} s_date;

		// Nie możemy wyliczać struktury, 
		// podajemy jedynie nazwy jej pól

		// Wypisz elementy 
		cout << "D/M/Y:" << s_date.fDay << "/" << 
			s_date.fMonth << "/" << 
			s_date.fYear << endl;


		// Pobierz elementy do osobnych obiektów
		// bez powiązania strukturalnego
		const auto [ d, m, y ] = s_date;

		// Wypisz elementy 
		cout << "D/M/Y:" << d << "/" << 
			m << "/" << y << endl;

	}

}



