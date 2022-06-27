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





#pragma once



#include <memory>
#include <cassert>




// Deklaracje zapowiadająca klasy
class TVisitor;



// Deklaracja zapowiadająca klasy bazowej dla hierarchii węzłów.
class TNode;

// Wskaźnik posiadający obiekt – możemy zadeklarować std::unique_ptr
// tylko z zadeklarowaną klasą TNode:
using Node_UP = std::unique_ptr< TNode >;

// Wskaźnik bez posiadania
using NodePtr = TNode *;




// To jest klasa interfejsu reprezentująca węzeł
// w drzewie – istnieje tylko w celu umożliwienia dziedziczenia
// po niej, a jej obiekty nie mogą być tworzone.
class TNode
{

protected:

	// Umieszczenie konstruktora w sekcji protected również jest sposobem
	// na oznaczenie klasy jako bazowej, ponieważ wtedy mogą być tworzone tylko obiekty
	// klas pochodnych.
	TNode( void ) = default;


public:

	// Na potrzeby wskazania, że klasa jest interfejsem abstrakcyjnym,
	// jej destruktor jest czysto wirtualną funkcją,
	// co jest wskazywane przez dodanie = 0 do deklaracji.
	virtual ~TNode() = 0; /*{}*/

public:

	// Czysto wirtualne funkcje mogą mieć implementacje,
	// ale nie jest to wcale wymagane, chyba że są wywoływane.
	// Typy pochodne muszą dostarczać swoje własne implementacje, jeśli
	// są tworzone ich obiekty.
	// Accept pozwala na działanie wizytatora.
	virtual void Accept( TVisitor & v ) const = 0;

public:

	// Operacja klonowania się – brak implementacji
	// dla Clone w klasie bazowej.
	virtual Node_UP Clone( void ) const = 0;

};



// Liść (obiekt) z wartością, taką jak
// liczba, ciąg znaków itd.
template < typename V >
class ValueLeafNode : public TNode
{

private:

	V		fVal {};	// przechowywana wartość

public:

	ValueLeafNode( void ) : fVal() {}
	explicit ValueLeafNode( const V & val ) : fVal( val ) {}
	
	virtual ~ValueLeafNode() = default;

	ValueLeafNode( const ValueLeafNode & ) = default;
	ValueLeafNode( ValueLeafNode && ) noexcept = default;

	ValueLeafNode & operator = ( const ValueLeafNode & ) = default;
	ValueLeafNode & operator = ( ValueLeafNode && ) noexcept = default;


public:


	V GetValue( void ) const { return fVal; }

	// Przyjmij wizytatora
	void Accept( TVisitor & v ) const override
	{
		v.Visit( * this );
	}

public:

	// Stwórz swoją kopię
	Node_UP Clone( void ) const override;

};


// Liść z wartością zmiennoprzecinkową
using NumberLeafNode = ValueLeafNode< double >;


// Klasa do reprezentowania dowolnego operatora binarnego
class BinOperator : public TNode
{

private:

	Node_UP		fLeftChild;		// Wskaźnik z posiadaniem do lewego poddrzewa
	Node_UP		fRightChild;	// Wskaźnik z posiadaniem do prawego poddrzewa

public:

	BinOperator( void ) = default;
	BinOperator( Node_UP left, Node_UP right ) : fLeftChild( std::move( left ) ), fRightChild( std::move( right ) ) {}

	virtual ~BinOperator () = default;

protected:

	// Nie zezwalają na proste (płytkie) kopiowanie.
	// Do kopiowania użyj Clone()
	BinOperator( const BinOperator & ) = delete;
	BinOperator( const BinOperator && ) = delete;

	BinOperator & operator = ( const BinOperator & ) = delete;
	BinOperator & operator = ( const BinOperator && ) = delete;

public:

	NodePtr		GetLeftChild( void ) const { assert( fLeftChild != nullptr ); return fLeftChild.get(); }
	NodePtr		GetRightChild( void ) const { assert( fRightChild != nullptr ); return fRightChild.get(); }

	// Przekazywanie w celu przejęcia na własność
	void		AdoptLeftChild( Node_UP up ) { fLeftChild = std::move( up ); }
	void		AdoptRightChild( Node_UP up ) { fRightChild = std::move( up ); }

public:

	void Accept( TVisitor & v ) const override = 0;

public:

	// Sklonuj się – to jest klasa pochodna, ale
	// Clone jest czysto wirtualna i nie mamy 
	// jej implementacji.
	Node_UP Clone( void ) const override = 0;

};



// Konkretny operator binarny
class PlusOperator : public BinOperator
{

public:

	PlusOperator( void ) = default;
	PlusOperator( Node_UP left, Node_UP right ) 
		: BinOperator( std::move( left ), std::move( right ) )	// zainicjalizuj klasę bazową
	{}

	virtual ~PlusOperator() = default;

	// Kopiowanie obiektów zabronione w klasie bazowej

public:

	void Accept( TVisitor & v ) const override;

public:

	// Odtwórz się
	Node_UP Clone( void ) const override;

};



class MinusOperator : public BinOperator
{

public:

	MinusOperator( void ) = default;
	MinusOperator( Node_UP left, Node_UP right ) 
		: BinOperator( std::move( left ), std::move( right ) )	// init base class 
	{}

	virtual ~MinusOperator() = default;

	// Object copying disallowed by the base class

public:

	void Accept( TVisitor & v ) const override;

public:

	// Re-create yourself
	Node_UP Clone( void ) const override;

};



class MultOperator : public BinOperator
{

public:

	MultOperator( void ) = default;
	MultOperator( Node_UP left, Node_UP right ) 
		: BinOperator( std::move( left ), std::move( right ) )	// init base class 
	{}

	virtual ~MultOperator() = default;

	// Object copying disallowed by the base class

public:

	void Accept( TVisitor & v ) const override;

public:

	// Re-create yourself
	Node_UP Clone( void ) const override;

};



class DivOperator : public BinOperator
{

public:

	DivOperator( void ) = default;
	DivOperator( Node_UP left, Node_UP right ) 
		: BinOperator( std::move( left ), std::move( right ) )	// init base class 
	{}

	virtual ~DivOperator() = default;

	// Object copying disallowed by the base class

public:

	void Accept( TVisitor & v ) const override;

public:

	// Re-create yourself
	Node_UP Clone( void ) const override;

};


