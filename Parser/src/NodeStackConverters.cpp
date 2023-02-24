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
#include <cmath>


#include "ExpressionTreeBuilderInterpreter.h"


using std::cout, std::endl;
using std::string;
using std::vector;



///////////////////////////////////////////////////////////////////////////////////////////////


using NodeVec = ExpressionTreeBuilderInterpreter::NodeStack::DataContainer;


using LeafValType = double;


// Oblicza wartość stosu
LeafValType ComputeValueFrom( const NodeVec & node_vec )
{
	auto retVal { 0.0 };

	const auto kNumOfElems = node_vec.size();
	if( kNumOfElems == 0 )
		return retVal;		// Pusty node_vec, zwróć zero i zakończ


	// Algorytm jest następujący:
	// - Przechodzimy po stosie węzłów:
	// -	po napotkaniu liścia umieszczamy jego wartość na stosie auxStack
	// -	po napotkaniu operatora bierzemy dwie odgórne wartości, wykonujemy
	//	działanie i rezultat umieszczamy z powrotem na stosie auxStack
	CppBook::TStackFor< LeafValType, 1000 >		auxStack;



	// Przejdź po wszystkich węzłach, zaczynając od indeksu 0
	for( const auto & node : node_vec )
	{
		assert( node );

		if( typeid( * node ) == typeid( NumberLeafNode ) )
		{
			// Węzeł liścia NumberLeafNode
			auxStack.Push( dynamic_cast< NumberLeafNode & >( * node ).GetValue() );
		}
		else
		{
			// Operator binarny – ale nie wiemy jeszcze który

			assert( auxStack.GetStackSize() >= 2 );	

			LeafValType leftNumVal {}, rightNumVal {};

			auxStack.Pop( rightNumVal );	// Pobierz wartości z samej góry
			auxStack.Pop( leftNumVal );

			// Sprawdź, jakiego rodzaju operacja znajduje się w węźle
			if( dynamic_cast< PlusOperator * >( node.get() ) )
				auxStack.Push( leftNumVal + rightNumVal );
			else
				if( dynamic_cast< MinusOperator * >( node.get() ) )
					auxStack.Push( leftNumVal - rightNumVal );
				else
					if( dynamic_cast< MultOperator * >( node.get() ) )
						auxStack.Push( leftNumVal * rightNumVal );
					else
						if( dynamic_cast< DivOperator * >( node.get() ) )
							if(	std::fabs( rightNumVal ) > 1e-32 ) 
								auxStack.Push( leftNumVal / rightNumVal ); 
							else 
								throw std::overflow_error( "Div by 0" );
						else
							assert( false ); // Nie może się zdarzyć – sprawdzamy w wersji debug
		}


	}

	// Przejmij ostatni węzeł ze stosu lub zwróć pusty.
	assert( auxStack.GetStackSize() == 1 );
	auxStack.Pop( retVal );

	return retVal;
}





// ------------------------------------------
// Oblicza wartość ze stosu węzłów.
// Działa podczas kompilowania z parametrem
// BUILD_THE_TREE ustawionym na 0
// (w ExpressionTreeBuilderInterpreter.h)
void RPN_Value_Test( void )
{
#if BUILD_THE_TREE == 1
	assert( false );		// Bezpiecznik gwarantujący kompilację z odpowiednim parametrem
#endif

	ExpressionTreeBuilderInterpreter		exprParser;

	string good_expr( "(1+2)*(3+(4+5))/(6-7)" );		// Ciąg wyrażeń

	// Wywołajmy tylko operator () z klasy bazowej
	//if( exprParser.BaseClass::operator()( good_expr ) )
	if( ( & exprParser )->BaseClass::operator()( good_expr ) )
	{
		try
		{
			std::cout << "Val = " << ComputeValueFrom(  exprParser.GetNodeStack().GetDataContainer()  ) << endl;
		}
		catch( std::exception & e )
		{
			std::cerr << e.what() << endl;
		}
	}
	else
	{
		cout << "Syntax error!\n" << good_expr << "\n";
		cout << std::string( exprParser.GetCurPos(), ' ' ) << '^' << "\nExiting ..." << endl;
	}


}



///////////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////
// Converts a stack of nodes into a syntax tree.
///////////////////////////////////////////////////////////
//
// INPUT:	node_vec - a vector underlying a stack with 
//				nodes inserted by the parser	
//
// OUTPUT:	A smart pointer to the root of the built syntax tree
//
// REMARKS: Returned pointer will be empty if stack is empty.
//			The objects in the node_vec will be overtaken
//			to the built tree whose root node is returned.
//
Node_UP ConvertStack_2_SyntaxTree( NodeVec & node_vec )
{
	const auto kNumOfElems = node_vec.size();
	if( kNumOfElems == 0 )
		return Node_UP();		// return an empty object

	// Traverse all nodes, starting at index 0
	for( const auto i : CppBook::range( kNumOfElems ) )
	{

		if( auto bin_op = dynamic_cast< BinOperator * >( node_vec[ i ].get() ) )
		{
			// If bin op, then overtake its two preceeding nodes,
			// whatever it is, and join as its left and right child

			assert( i >= 2 );		// 

			Node_UP left, right;	// empty at the beginning

			// Go downward and find two nodes not yet overtaken
			// We have to use the signed type 'int' here to properly compare k >= 0
			for( int k = static_cast< int >( i - 1 ); k >= 0; -- k )
			{
				if( node_vec[ k ] != nullptr )
				{
					// First is right
					if( right == nullptr )
					{
						right = std::move( node_vec[ k ] );
					}
					else
					{
						if( left == nullptr )
						{
							left = std::move( node_vec[ k ] );
							break;		// we are done, exit the loop asap
						}
					}
				}
			}

			assert( left != nullptr );
			assert( right != nullptr );

			bin_op->AdoptLeftChild( std::move( left ) );		// connect the nodes
			bin_op->AdoptRightChild( std::move( right ) );

		}

	}

	// Overtake the last node from the stack or return empty.
	return node_vec.size() > 0 ? std::move( node_vec.back() ) : Node_UP();
}






void RPN_Tree_Test( void )
{
#if BUILD_THE_TREE == 1
	assert( false );		// A fuse to ensure we compiled with the proper parameter
#endif

	ExpressionTreeBuilderInterpreter		exprParser;

	string good_expr( "(1+2)*(3+(4+5))/(6-7)" );		// this string is hard coded - make it user entered

	// Let us call only the base class operator ()
	if( exprParser.BaseClass::operator()( good_expr ) == false )
	{
		cout << "Syntax error!\n" << good_expr << "\n";
		cout << std::string( exprParser.GetCurPos(), ' ' ) << '^' << "\nExiting ..." << endl;
		return;		// Exiting ...
	}


	// Build a syntax tree from the stack and take a pointer to the root of the tree
	Node_UP		theRoot { ConvertStack_2_SyntaxTree( exprParser.GetNodeStack().GetDataContainer() ) };
	assert( theRoot );


	// Print structure of the parsing tree
	theRoot->Accept( evom( PrintVisitor() ) );


	// Evaluate the expression
	try
	{
		EvalVisitor		evalVisitor;
		theRoot->Accept( evalVisitor );		// Can throw on zero division
		std::cout << "Val = " << evalVisitor.GetValue() << endl;
	}
	catch( std::exception & e )
	{
		std::cerr << e.what() << endl;
	}

}





