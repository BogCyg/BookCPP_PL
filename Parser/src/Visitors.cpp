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


#include "Nodes.h"
#include "Visitors.h"


// ===================================================================


void EvalVisitor::Visit( const NumberLeafNode & n )
{
	fValue = n.GetValue();
}

void EvalVisitor::Visit( const PlusOperator & n )
{
	auto [ l, r ] = LeftRightValues( n );
	fValue = l + r;	// bieżąca wartość jest sumą lewego i prawego węzła
}


void EvalVisitor::Visit( const MinusOperator & n )
{
	auto [ l, r ] = LeftRightValues( n );
	fValue = l - r;	// cbieżąca wartość jest różnicą lewego i prawego węzła
}


void EvalVisitor::Visit( const MultOperator & n )
{
	auto [ l, r ] = LeftRightValues( n );
	fValue = l * r;	// bieżąca wartość jest iloczynem lewego i prawego węzła
}


void EvalVisitor::Visit( const DivOperator & n )
{
	auto [ l, r ] = LeftRightValues( n );

	if( std::fabs( r ) < kDivThresh )
		throw std::overflow_error( "Div by 0" );

	fValue = l / r;	// bieżąca wartość jest ilorazem lewego i prawego węzła
}


///////////////////////////////////////////////////////////
// Pomocnicza funkcja do przetwarzania lewego i prawego węzła.
///////////////////////////////////////////////////////////
//
// WEJŚCIE: 	n – referencja do węzła binarnego		
//
// WYJŚCIE: 	para wartości dla lewego i prawego węzła
//
EvalVisitor::LR_Pair EvalVisitor::LeftRightValues( const BinOperator & n )
{
	n.GetLeftChild()->Accept( * this ); // Najpierw lewy – ma to znaczenie (łącz. lewos.).
	auto left_val { fValue };		// Zachowaj wartość lewego

	n.GetRightChild()->Accept( * this );
	auto right_val { fValue };	// Zachowaj wartość prawego

	return std::make_tuple( left_val, right_val );
}



// ===================================================================



void PrintVisitor::Visit( const NumberLeafNode & n )
{
	std::cout << std::string( fDepthLevel, ' ' ) << ' ';
	std::cout << std::string( fDL_Step - 1, '-' ) << n.GetValue() << std::endl;
}

void PrintVisitor::Visit( const PlusOperator & n )
{
	LeftRightProcess( n, '+' );
}


void PrintVisitor::Visit( const MinusOperator & n )
{
	LeftRightProcess( n, '-' );
}


void PrintVisitor::Visit( const MultOperator & n )
{
	LeftRightProcess( n, '*' );
}


void PrintVisitor::Visit( const DivOperator & n )
{
	LeftRightProcess( n, '/' );
}


// Here we have an infix operation: left-this-right
void PrintVisitor::LeftRightProcess( const BinOperator & n, char op )
{
	auto prev_dl = fDepthLevel;	// get current indentation level

	fDepthLevel += fDL_Step;	// increase indentation 

	n.GetRightChild()->Accept( * this );

	std::string sepa( fDepthLevel, ' ' );
	std::cout << sepa << '|' << std::endl;
	std::cout << sepa << op << std::endl;
	std::cout << sepa << '|' << std::endl;

	n.GetLeftChild()->Accept( * this );

	fDepthLevel = prev_dl;		// restore previous indent level
}






