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





#include <filesystem>
#include <io.h>
#include <fcntl.h>


#include "CurrencyCalcPlayGround.h"

#if 0
namespace CurrExchanger
{

	void Run( void );

}


namespace CurrExchanger
{
	namespace OnLine_CurrExchanger
	{
		void Run( void );
	}
}
#endif


#include <iostream>
#include <locale>

// Twórz prosty main(), kod umieść w innych komponentach
int main( void )
{
	setlocale( /*LC_ALL*/LC_CTYPE, "Polish" );
	CurrExchanger::OnLine_CurrExchanger::Run();
	return 0; // Choć nie jest to wymagane, zwróć wartość z main
}






