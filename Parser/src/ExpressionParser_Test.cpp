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


#include "ExpressionTreeBuilderInterpreter.h"


using std::cout, std::endl;
using std::string;
using std::vector;



///////////////////////////////////////////////////////////////////////////////////////////////


// -------------------------------
void SimpleExpression_Test( void )
{

	TSimpleExpressionInterpreter		theInterpreter;

	const vector< std::string >	expr_vec	{
												"2+3*(7+3)",
												"2+3+4+5+6+",
												"(((5)))",
												"((2+3)*(4+5)+7)/9",
												"2++3*(7+3)"
											};

	// Sprawdź składnię każdego ciągu wyrażenia
	for( const auto & expr : expr_vec )
		cout << expr << " is " << ( theInterpreter( expr ) ? "OK\n" : "not OK\n" );

}



///////////////////////////////////////////////////////////////////////////////////////////////




// -------------------------
void SyntaxTree_Test( void )
{

	ExpressionTreeBuilderInterpreter		exprParser;

	//string good_expr( "2+3*4" );		// ten tekst jest trwale zakodowany - spraw, by wprowadził go użytkownik
	//string good_expr( "2+3*7+3" );		// ten tekst jest trwale zakodowany - spraw, by wprowadził go użytkownik
	//string good_expr( "2/3+(7+3)" );		// ten tekst jest trwale zakodowany - spraw, by wprowadził go użytkownik
	//string good_expr( "5*(3+2*5)/(2/3+(7+3))" );		// ten tekst jest trwale zakodowany - spraw, by wprowadził go użytkownik
	//string good_expr( "(2+3)*(4+5)*(6+7)" );		// ten tekst jest trwale zakodowany - spraw, by wprowadził go użytkownik
	//string good_expr( "2*3*4" );		// tten tekst jest trwale zakodowany - spraw, by wprowadził go użytkownik
	//string good_expr( "(1+2)*(3+4+5)/(6-7)" );		// ten tekst jest trwale zakodowany - spraw, by wprowadził go użytkownik
	string good_expr( "(1+2)*(3+(4+5))/(6-7)" );		// ten tekst jest trwale zakodowany - spraw, by wprowadził go użytkownik

	if( exprParser( good_expr ) == false )
	{
		cout << "Syntax error!\n" << good_expr << "\n";
		cout << std::string( exprParser.GetCurPos(), ' ' ) << '^' << "\nExiting ..." << endl;
		return;
	}



	// Tutaj możemy zrobić coś z drzewem, np. uruchomić wizytatora

	// Pozyskaj wskaźnik do korzenia drzewa
	NodePtr		theRoot { exprParser.GetRoot() };
	assert( theRoot );


	// Wypisz strukturę drzewa parsowania
	theRoot->Accept( evom( PrintVisitor() ) );	


	// ------------------------------
	// Jak skopiować drzewo?
	PlusOperator	p1, p2;		// ok
	//PlusOperator	p3( p2 );	// błąd, nie da się skonstruować kopii
	//p1 = p2;					// błąd, brak kopii poprzez przypisanie



	// Sklonujmy drzewo, aby przykładowo użyć go 
	// w osobnym wątku.
	Node_UP	theSecondTree { theRoot->Clone() };


	// Dokonaj ewaluacji wyrażenia
	EvalVisitor		evalVisitor;
	try
	{
		theSecondTree->Accept( evalVisitor );		// Może zgłosić dzielenie przez zero
		std::cout << "Val = " << evalVisitor.GetValue() << endl;
	}
	catch( std::exception & e )
	{
		std::cerr << e.what() << endl;
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////












