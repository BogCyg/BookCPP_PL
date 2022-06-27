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


#define ALLOW_INHERITANCE 1

#include "LongNumberFor.h"






/////////////////////////////////////////////////////////////////////////////////
// Wersja "jest"
class PESEL : public TLongNumberFor< 11 >
{
	public:

		using BaseClass = TLongNumberFor< 11 >;
		using BaseClass::GetNumberAt;

	private:

		// Pewne stałe specyficzne dla polskiego numeru PESEL
		enum { kBirthYear_Dec = 10, kBirthYear_Sngl = 9, kSex = 1 };

	public:

		enum class ESex { kMan, kWoman };

	public:

		PESEL( void ) {}
		PESEL( const string & s ) : BaseClass( s ) {}		// lasa bazowa z ciągu znaków
		
		virtual ~PESEL() {}		// musi być wirtualny, dlaczego?
								// aponadto TLongNumberFor<> powinna mieć wirtualny destruktor
	public:

		auto GetYearOfBirth( void ) 
		{ 
			return GetNumberAt( kBirthYear_Dec ) * 10 + GetNumberAt( kBirthYear_Sngl );
		}

		ESex GetSex( void )
		{
			return ( GetNumberAt( kSex ) & 0x01 ) == 0x01 ? ESex::kMan : ESex::kWoman;
		}
};



