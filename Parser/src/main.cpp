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



#include "ExpressionTreeBuilderInterpreter.h"


void SimpleExpression_Test( void );
void SyntaxTree_Test( void );
void RPN_Value_Test( void );
void RPN_Tree_Test( void );


int main()
{

	SimpleExpression_Test();	

#if BUILD_THE_TREE == 1
	SyntaxTree_Test();
#else
	RPN_Value_Test();
	RPN_Tree_Test();
#endif	


}


