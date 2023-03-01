// ==========================================================================
//
// Oprogramowanie napisane przez prof. Bogus³awa Cyganka do u¿ytku z ksi¹¿k¹:
// ==> Programowanie w jêzyku C++. Wprowadzenie dla in¿ynierów. PWN 2023 <==
//
// Oprogramowanie jest dostarczane w stanie takim, w jakim jest, i do celów edukacyjnych
// bez ¿adnych gwarancji ani odpowiedzialnoœci za jego u¿ycie w jakiejkolwiek aplikacji.
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




#include "Nodes.h"
#include "Visitors.h"


// ----------------------------------------

// Although it is declared as pure virtual = 0,
// it also needs a full definition. However, this
// cannot be added in the header due to the =0 specifier.
TNode::~TNode() 
{
}

// ----------------------------------------


void PlusOperator::Accept( TVisitor & v ) const
{
	v.Visit( * this );
}

void MinusOperator::Accept( TVisitor & v ) const
{
	v.Visit( * this );
}

void MultOperator::Accept( TVisitor & v ) const
{
	v.Visit( * this );
}

void DivOperator::Accept( TVisitor & v ) const
{
	v.Visit( * this );
}


template <>
void NumberLeafNode::Accept( TVisitor & v ) const
{
	v.Visit( * this );
}


template <>
Node_UP NumberLeafNode::Clone( void ) const
{
	return std::make_unique< ValueLeafNode< double > >( * this );
}



// ----------------------------------------


// Node_UP NumberLeafNode::Clone( void ) const
// {
// 	return std::make_unique< NumberLeafNode >( * this );
// }


Node_UP PlusOperator::Clone( void ) const
{
	return std::make_unique< PlusOperator >( GetLeftChild()->Clone(), GetRightChild()->Clone() );
}

Node_UP MinusOperator::Clone( void ) const
{
	return std::make_unique< MinusOperator >( GetLeftChild()->Clone(), GetRightChild()->Clone() );
}

Node_UP MultOperator::Clone( void ) const
{
	return std::make_unique< MultOperator >( GetLeftChild()->Clone(), GetRightChild()->Clone() );
}

Node_UP DivOperator::Clone( void ) const
{
	return std::make_unique< DivOperator >( GetLeftChild()->Clone(), GetRightChild()->Clone() );
}

