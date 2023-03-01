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



#include <iostream>
#include <string>
#include <vector>



// Łączy dwa różne obiekty pod jednym dachem
struct MonthDays
{
	std::string		fName {};	// Użyj {} do zainicjalizowania danych składowych.
	int				fDays {};	// Puste nawiasy klamrowe {} do zainicjalizowania wartością 0.
};


// Tworzy i wyświetla prosty kalendarz
void SimpleCalendar( void )
{
	const std::vector< MonthDays >	calendar {	
												{ "January",		31 },
												{ "February",		28 },
												{ "March",			31 },
												{ "April",			30 },
												{ "May",			31 },
												{ "June",			30 },
												{ "July",			31 },
												{ "August",			31 },
												{ "September",		30 },
												{ "October",		31 },
												{ "November",		30 },
												{ "December",		31 }

										};

	// Wypisz je na ekran
	auto sum_days { 0 };
	for( auto month : calendar )
	{
		sum_days += month.fDays;
		std::cout << month.fName << " has " << month.fDays << " days\n";
	}

	std::cout << "\nTotal days: " << sum_days << std::endl;
}





