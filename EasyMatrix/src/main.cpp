// ==========================================================================
//
// Oprogramowanie napisane przez prof. Bogus�awa Cyganka do u�ytku z ksi��k�:
// ==> Programowanie w j�zyku C++. Wprowadzenie dla in�ynier�w. PWN 2023 <==
//
// Oprogramowanie jest dostarczane w stanie takim, w jakim jest, i do cel�w edukacyjnych
// bez �adnych gwarancji ani odpowiedzialno�ci za jego u�ycie w jakiejkolwiek aplikacji.
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


// System headers in < >
#include <iostream>


// Own header in " "
#include "EMatrix.h"


void Easy_Matrix_Zeroth_Test( void );
void Easy_Matrix_First_Test( void );
void Easy_Matrix_Second_Test( void );
void Easy_Matrix_Third_Test( void );
void Easy_Matrix_Fourth_Test( void );


int main()
{
	
#if EM_VER == 1


	Easy_Matrix_First_Test();

	Easy_Matrix_Second_Test();

#else

	Easy_Matrix_Zeroth_Test();

	Easy_Matrix_Third_Test();

	Easy_Matrix_Fourth_Test();

#endif

	char c{};
	std::cin >> c;

	return c;
}






