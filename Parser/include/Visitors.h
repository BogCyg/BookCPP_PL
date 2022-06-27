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



#include <tuple>


class TNode;

using NumberLeafNode = ValueLeafNode< double >;

class BinOperator;
class PlusOperator;
class MinusOperator;
class MultOperator;
class DivOperator;


// Abstrakcyjna klasa bazowa dla wszystkich wizytatorów
class TVisitor
{

public:

	TVisitor () = default;
	virtual ~TVisitor () = default;

public:

	// Czysto wirtualna funkcja do odwiedzania tworzonych węzłów
	virtual void Visit( const NumberLeafNode & n ) = 0;
	virtual void Visit( const PlusOperator & n ) = 0;
	virtual void Visit( const MinusOperator & n ) = 0;
	virtual void Visit( const MultOperator & n ) = 0;
	virtual void Visit( const DivOperator & n ) = 0;

};


// Wizytator dokonujący ewaluacji wyrażenia
class EvalVisitor : public TVisitor
{
private:

	double	fValue {};

	const double kDivThresh { 1e-12 };

public:

	double GetValue( void ) const { return fValue; }


protected:

	using LR_Pair = std::tuple< double, double >;

	///////////////////////////////////////////////////////////
	// Pomocnicza funkcja do przetwarzania lewego i prawego węzła.
	///////////////////////////////////////////////////////////
	//
	// WEJŚCIE: 	n – referencja do węzła binarnego 		
	//
	// WYJŚCIE: 	para wartości dla lewego i prawego węzła
	//
	EvalVisitor::LR_Pair LeftRightValues( const BinOperator & n );


public:

	// Zestaw przeciążonych funkcji dla każdego węzła w drzewie parsowania
	void Visit( const NumberLeafNode & n ) override;
	void Visit( const PlusOperator & n ) override;
	void Visit( const MinusOperator & n ) override;
	void Visit( const MultOperator & n ) override;
	void Visit( const DivOperator & n ) noexcept( false ) override;	// może zgłosić wyjątek 
									// - wskazywane przez specyfikator noexcept( false )
};



// -------------------------------------------------------------

// Wizytator do wypisywania struktury drzewa
class PrintVisitor : public TVisitor
{
private:

	int		fDepthLevel {};		// Bieżąca wartość wcięcia

	const int fDL_Step { 3 };	// krok wcięcia

protected:

	///////////////////////////////////////////////////////////
	// Pomocnicza funkcja do wypisywania operatora binarnego.
	///////////////////////////////////////////////////////////
	//
	// WEJŚCIE: 	n – referencja do węzła binarnego	
	//		op – znak symbolu operatora
	//
	// WYJŚCIE: 	brak
	//
	void LeftRightProcess( const BinOperator & n, char op );

public:

	// Zestaw przeciążonych funkcji dla każdego węzła w drzewie parsowania
	void Visit( const NumberLeafNode & n ) override;
	void Visit( const PlusOperator & n ) override;
	void Visit( const MinusOperator & n ) override;
	void Visit( const MultOperator & n ) override;
	void Visit( const DivOperator & n ) override;

};



