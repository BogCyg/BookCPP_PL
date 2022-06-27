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
#include <iostream>
#include <memory>
#include <algorithm>


#include "Nodes.h"
#include "Visitors.h"
#include "TheStack.h"
#include "range.h"


#include "SimpleExpressionInterpreter.h"




// Interpreter, który buduje drzewa parsowania
class ExpressionTreeBuilderInterpreter : public TSimpleExpressionInterpreter
{
	public:


		ExpressionTreeBuilderInterpreter( void ) = default;
		virtual ~ExpressionTreeBuilderInterpreter() = default;


		// Brak zezwolenia na płytkie kopiowanie z powodu fRoot i innych składowych
		ExpressionTreeBuilderInterpreter( const ExpressionTreeBuilderInterpreter & )	= delete;
		ExpressionTreeBuilderInterpreter( const ExpressionTreeBuilderInterpreter && )	= delete;

		ExpressionTreeBuilderInterpreter & operator = ( const ExpressionTreeBuilderInterpreter & )	= delete;
		ExpressionTreeBuilderInterpreter & operator = ( const ExpressionTreeBuilderInterpreter && ) = delete;

	public:

		///////////////////////////////////////////////////////////
		// Operator funkcyjny dopasowujący wyrażenie pod kątem spełnienia
		// gramatyki.
		///////////////////////////////////////////////////////////
		//
		// WEJŚCIE:	in_str - ciąg z wyrażeniem wejściowym 		
		//
		// WYJŚCIE:	ttrue, gdy wyrażenie spełnia gramatykę, w przeciwnym razie false
		//
		// UWAGI:
		//			Jeśli zwraca false, fCurrPos wskazuje na 
		//			ostatnią dobrze dopasowaną pozycję.
		//
		virtual bool operator () ( const std::string & in_str )
		{
			if( BaseClass::operator()( in_str ) )	// Wywołaj parser bazowy
				return fNodeStack.Pop( fRoot );		// Zdejmij węzeł ze stosu

			return false;
		}

	public:	

		using BaseClass = TSimpleExpressionInterpreter;
	
		using NodeStack = CppBook::UP_Stack_1000< TNode >;		// Przydatne aliasy stosu

	private:		
		
		NodeStack	fNodeStack;			// Stos do przechowywania tymczasowych gałęzi drzewa

		Node_UP		fRoot;				// Węzeł główny drzewa parsowania

	public:

		NodePtr		GetRoot( void ) { return fRoot.get(); }
	
		NodeStack &	GetNodeStack( void ) { return fNodeStack; }	


	protected:

		//D -> 0 | 1 | 2 | ... | 9
		virtual bool Digit_Fun( void )
		{
			if( Match( '0' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 0.0 ) ); return true; } 			
			if( Match( '1' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 1.0 ) ); return true; } 
			if( Match( '2' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 2.0 ) ); return true; } 
			if( Match( '3' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 3.0 ) ); return true; } 
			if( Match( '4' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 4.0 ) ); return true; } 
			if( Match( '5' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 5.0 ) ); return true; } 
			if( Match( '6' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 6.0 ) ); return true; } 
			if( Match( '7' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 7.0 ) ); return true; } 
			if( Match( '8' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 8.0 ) ); return true; } 
			if( Match( '9' ) ) { fNodeStack.Push( std::make_unique< NumberLeafNode >( 9.0 ) ); return true; } 

			return false;
		}


		// E' -> + T E' | - T E' | e
		virtual bool Expr_Prime_Fun( void )
		{
			if( Match( '+' ) == true )
			{
				if( Term_Fun() )		// produkcja: + T E'
				{
					CreateSubTree( std::make_unique< PlusOperator >() );
					return Expr_Prime_Fun();
				}
				else
				{
					return false;
				}
			}
			else
			{
				if( Match( '-' ) == true )
				{
					if( Term_Fun() )		// produkcja: - T E'
					{
						CreateSubTree( std::make_unique< MinusOperator >() );
						return Expr_Prime_Fun();
					}
					else
					{
						return false;
					}				
				}
			}

			return true;					// produkcja: e
		}



		// T' -> * F T' | / F T' | e
		virtual bool Term_Prime_Fun( void )
		{
			if( Match( '*' ) == true )
			{
				if( Factor_Fun() )		// produkcja: * F T
				{
					CreateSubTree( std::make_unique< MultOperator >() );
					return Term_Prime_Fun();
				}
				else
				{
					return false;
				}			
			}
			else
			{
				if( Match( '/' ) == true )
				{
					if( Factor_Fun() )		// produkcja: / F T'
					{
						CreateSubTree( std::make_unique< DivOperator >() );
						return Term_Prime_Fun();
					}
					else
					{
						return false;
					}
				}
			}

			return true;					// produkcja: e
		}




	protected:

		///////////////////////////////////////////////////////////
		// Buduje gałąź drzewa parsowania
		///////////////////////////////////////////////////////////
		//
		// WEJŚCIE:	bin_op - inteligentny wskaźnik z wejściowym operatorem binarnym 		
		//
		// WYJŚCIE:	węzeł
		//
		// UWAGI: obiekt przechowywany w bin_op jest pozyskiwany i umieszczany na stosie
		//
		void CreateSubTree( std::unique_ptr< BinOperator > bin_op )
		{
#define BUILD_THE_TREE 0
#if BUILD_THE_TREE == 1			
			
			assert( fNodeStack.GetStackSize() >= 2 );

			Node_UP left, right;

			fNodeStack.Pop( right );	// Ściągnij prawe podwyrażenie
			fNodeStack.Pop( left );		// Ściągnij lewe podwyrażenie

			bin_op->AdoptLeftChild( std::move( left ) );	// Połącz lewe
			bin_op->AdoptRightChild( std::move( right ) );	// Połącz prawe
#endif 

			fNodeStack.Push( std::move( bin_op ) ); // mieść na stosie
			assert( bin_op.get() == nullptr );		// Wejściowy bin_op jest osierocony
		}

};








