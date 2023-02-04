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
#include <fstream>
#include <string>
#include <memory>
#include <functional>
#include <cassert>

#include "range.h"

using namespace std;
using CppBook::range;


///////////////////////////////////////////////////////////////////////////////////////////////


// An example of memory leak generation 
// DO NOT USE THIS CODE !!
#if 0
bool ProcessFile( const string fileName )
{
	const int kBufSize = 256;
	char * buf = new char[ kBufSize ];		// allocate a buffer on the heap

	ifstream	file( fileName );
	if( file.is_open() == false )
	{
		return false;	// cannot open a file, exiting ... 
	}						// oops! - buf is not destroyed - a memory leak is generated !

	file.read( buf, kBufSize );	// file open OK, read to the buffer
	// do something ...

	delete [] buf;		// delete the buffer

	return true;		// everything OK, exit
}
#endif 


// Use std::vector as an underlying data container (data allocated on the heap)
bool ProcessFile_1( const string fileName )
{
	const int kBufSize = 256;
	std::vector< char >	buf( kBufSize );		// allocate a buffer on the heap

	ifstream	file( fileName );
	if( file.is_open() == false )
	{
		return false;	// cannot open a file, exiting ... 
	}					// OK, buf is an automatic object, it wil be destroyed

	file.read( & buf[0], kBufSize );	// file open OK, read to the buffer
	// do something ...

	return true;		// everything OK, exit
} // OK, buf is an automatic object, it will be destroyed


// Use std::unique_ptr smart pointer object
bool ProcessFile_2( const string fileName )
{
	const int kBufSize = 256;
	auto buf = std::make_unique< char >( kBufSize );		// allocate a buffer on the heap
															// but hold it with a unique_ptr
	ifstream	file( fileName );
	if( file.is_open() == false )
	{
		return false;	// cannot open a file, exiting ... 
	}					// OK, buf is an automatic object, it wil be destroyed
						// and it will deallocate memory from the heap

	file.read( buf.get(), kBufSize );	// file open OK, read to the buffer (use get)
	// do something ...

	return true;		// everything OK, exit
} // OK, buf is an automatic object, it will be destroyed








// DO NOT USE IT IN OPERATIONAL CODE!
// This class is ONLY TO SIMULATE 
// behavior of the so called auto pointers.
// The main mechanism is RAII (Resource 
// Acquisition Is Initialization) - a pointer
// is get during construction of a_p, and the
// memory pointed by this pointer is AUTOMATICALLY
// released by the destructor of the a_p.
template < typename T >
class a_p  // tylko przykład – zamiast tego użyj std::unique_ptr
{
private:

	T *	fPtr;	// wskaźnik do strzeżonego obiektu

public:

	a_p( T * p ) : fPtr( p ) {}

	// gdy a_p jest niszczony,  
	// niszczony jest również fPtr.
	~a_p() { delete fPtr; }	

public:

	// a_p może być używany jako zwykły wskaźnik dzięki przeciążeniu operatora *
	T & operator * ( void ) { return * fPtr; }

	// ...
};


void a_p_test( void )
{
	// Utwórz zaawansowany wskaźnik jako obiekt lokalny
	// - niech przechowuje wskaźnik do double
	a_p< double >	apd( new double( 0.0 ) );

	// Pracuj z apd jak ze zwykłym wskaźnikiem do double
	* apd = 5.0;		
	* apd *= 3.0;
	cout << "apd=" << * apd << " sizeof(apd) = " << sizeof( apd ) << endl;

	// apd zostanie tu zniszczony, ponieważ jest to obiekt automatyczny
	// Zniszczy on również przechowywany obiekt
}	// <==




class AClass
{
	string fStr;
public:
	AClass( const string & s = "" ) : fStr(s) {}
	~AClass() { cout << "AClass destructor" << endl; }

	const string GetStr( void ) const { return fStr; }
	void SetStr( const string & s ) { fStr = s; }
};






void unique_ptr_tests( void )
{
	// Heap allocate a single double object, init to 0.0, and create a unique_ptr
	unique_ptr< double > real_val_0( new double( 0.0 ) );	// good

	// Heap allocate a single double object, init to 0.0, and create a unique_ptr
	// via make_unique. Better, can use "auto".
	auto real_val_1( make_unique< double >( 0.0 ) );		// better

	assert( real_val_1.get() != nullptr );	// check the allocated memory ptr
	* real_val_1 = 3.14;	// use like any other pointer

	// ------------------------------------------------------------------------
	// Heap allocate an array of 16 double – access via the unique_ptr
	const int kElems = 16;

	unique_ptr< double [] > 	real_array_0( new double[ kElems ] );	// OK
	// but elements of real_array_0 are NOT initialized !

	auto				real_array_1( make_unique< double [] >( kElems ) );	// better
	// Elements of real_array_1 will be value initialized with double(), i.e. to 0.0	
	
	// ------------------------------------------------------------------------
	if( real_array_0 )	// check if memory has been allocated (calls operator bool()) 
	{
		// init elems
		std::fill( & real_array_0[ 0 ], & real_array_0[ kElems ], -1.0 );
		real_array_0[ 0 ] = 2.71;	// use real_array_0 as a simple array
		// ...
	}

	real_array_0.reset();		// reset the held pointer and delete all elements



	// -----------------------------------------------
	// AClass object on the heap, p_d takes care
	unique_ptr< AClass > p_d_1( new AClass( "Good" ) );

	// A better way is to use make_unique helper
	auto p_d_2( make_unique< AClass >( "Better" ) );

	if( p_d_2 )
	{
		cout << p_d_2->GetStr() << endl;		// access through the pointer
		cout << ( * p_d_2 ).GetStr() << endl;	// access through the object
	}

	//unique_ptr< AClass > p_d_3 = p_d_2;	// won't work, cannot copy
	unique_ptr< AClass > p_d_3 = std::move( p_d_2 );	// OK, can move to other smart ptr

	// An array of AClass objects on the heap adn p_d_4 
	const int kAClassElems = 4;
	auto p_d_4( make_unique< AClass [] >( kAClassElems ) );	// call default constructor for each


}




template< typename P >
using unique_ptr_with_deleter = unique_ptr< P, function< void( P * ) > >;

void unique_ptr_with_custom_deleters( void )
{

	// -----------------------------------------------
	// Examples of custom deleters for unique_ptr

	// Zdefiniuj niestandardowe usuwanie dla AClass ‐ funkcja lambda
	auto AClass_delete_fun = [] ( AClass * ac_ptr ) 
	{ 
		// Wypisz do dziennika ...
		delete ac_ptr; 
	};

	// ...
	unique_ptr< AClass, decltype( AClass_delete_fun ) > p_d_8( new AClass(), AClass_delete_fun );

	// Zdefiniuj własną metodę usuwania dla FILE ‐ funkcja lambda
	auto file_close_fun = [] ( FILE * f) { fclose( f ); };


	// ...
	unique_ptr_with_deleter< FILE > file( fopen( "myFile.txt", "r" ), file_close_fun );

}




void things_to_avoid_with_unique_ptr( void )
{
	{																		
		// Obiekt AClass na stercie, zajmuje się tym p_d
		auto p_d_0( new AClass( "No ..." ) );	// ups, zwykły wskaźnik

		delete p_d_0;			// pozbądź się go
	}

	{
		AClass * p_d_5 = new AClass;

		unique_ptr< AClass > p_d_6( p_d_5 );	// nie inicjalizuj za pomocą zwykłego wskaźnika

		// ...
		// gdzieś indziej ...
		unique_ptr< AClass > p_d_7( p_d_5 );	// źle, dwa wskaźniki unique_ptr do jednego obiektu
	}



	{

		// Wrong!!! new on unique_ptr should be forbidden!
		unique_ptr< AClass > * pxx = new unique_ptr< AClass >( new AClass( "me" ) );
		using AClass_up = unique_ptr< AClass >;
		auto pzz = make_unique< AClass_up >( make_unique< AClass >( "" ) );

	}

}



// Simple factory example

// Czysto wirtualna klasa bazowa
class B
{
public:
	virtual ~B() {}

	virtual void operator() ( void ) = 0;
};

// Klasy pochodne
class C : public B
{
public:
	virtual ~C() 
	{
		cout << "C is deleted" << endl;	
	}

	// Również wirtualny, ale override wystarczy, aby to wyrazić (pomijamy virtual)
	void operator() ( void ) override	
	{
		cout << "C is doing an action..." << endl;
	}
};

class D : public B
{
public:
	virtual ~D() 
	{
		cout << "D is deleted" << endl;	
	}

	void operator() ( void ) override
	{
		cout << "D is doing an action..." << endl;
	}
};

class E : public B
{
public:
	virtual ~E() 
	{
		cout << "E is deleted" << endl;	
	}

	void operator() ( void ) override
	{
		cout << "E is doing an action..." << endl;
	}
};




enum EClassId { kC, kD, kE };

auto Factory( EClassId id )
{
	switch( id )
	{
		case kC: return unique_ptr< B >( make_unique< C >() );
		case kD: return unique_ptr< B >( make_unique< D >() );
		case kE: return unique_ptr< B >( make_unique< E >() );

		default: assert( false );	// nie powinniśmy tu być
	}

	return unique_ptr< B >();	// może być pusty, nie powinniśmy tu dotrzeć
}

void FactoryTest( void )
{
	vector< unique_ptr< B > > theObjects; // = { Factory( kC ), Factory( kD ), Factory( kE ) };
					      // wektor zawierający inteligentne wskaźniki!
	theObjects.push_back( Factory( kC ) );		// jaka semantyka? przenoszenie
	
	theObjects.emplace_back( Factory( kD ) );	// tu będzie przenoszenie, ok

	theObjects.emplace_back( Factory( kE ) );

	theObjects[ theObjects.size() - 1 ] = Factory( kD );	// zamień (przenieś) E na D

	for( auto & a : theObjects )
		( * a )();		// wywołaj akcje za pomocą mechanizmu wirtualnego
}


/////////////////////////////////////////////////////////////////////

// More on passing to and from unique_ptr


class TMatrix
{
public:
	TMatrix( int cols, int rows ) {}
	// ... cała reszta
};




// ---------
// PRODUCENT
// Zwraca unique_ptr< TMatrix > 
auto	OrphanRandomMatrix( const int kCols, const int kRows /*, enum ERandType rand_type*/ )
{
	auto retMatrix( make_unique< TMatrix >( kCols, kRows ) );

	// ... wykonaj obliczenia

	return retMatrix;		// zwróć ciężki obiekt za pomocą semantyki przenoszenia
}


// ---------
// KONSUMENCI


// Jeśli zawsze przetwarzany jest obiekt, przekaż obiekt przez referencję lub stałą referencję (tylko do odczytu)
double ComputeDeterminant( const TMatrix & matrix )
{
	double retDeterminant {};

	// ... wykonaj obliczenia

	return retDeterminant;
}



// Ok, unique_ptr jest przekazywany przez stałą referencję, jednak wskaźnik
// do macierzy może mieć wartość nullptr ‐ możemy użyć tej cechy,
// jeśli chcemy mieć opcję przekazania pustego obiektu.
bool ComputeDeterminant( const unique_ptr< TMatrix > & matrix, double & outRetVal )
{
	if( ! matrix )
		return false;		// jeśli pusty wskaźnik, nie wykonuj wcale obliczeń

	outRetVal = ComputeDeterminant( * matrix );		// pozyskaj obiekt

	return true ;
}

// Przekaż przez referencję do unique_ptr ‐ możemy przejąć przechowywany obiekt
void TakeOverAndProcessMatrix( unique_ptr< TMatrix > & matrix )
{
	// Bez std::move się nie skompiluje; wystąpi błąd: "it is a deleted function"
	unique_ptr< TMatrix > myMatrix( move( matrix ) );	// przejmij ten obiekt
														// zmienia przekazaną "macierz" na pustą
	// ... wykonaj obliczenia

	// po zakończeniu nie będzie wcale obiektu matrix
}

// Taka wersja jest również możliwa – jednak możemy mieć matrix == nullptr,
// więc możliwe jest również, że matrix.get() == nullptr
void TakeOverAndProcessMatrix( unique_ptr< TMatrix > * matrix )
{
	if( matrix == nullptr )
		return;

	// Bez std::move się nie skompiluje; wystąpi błąd: "it is a deleted function"
	unique_ptr< TMatrix > myMatrix( move( * matrix ) );	// przejmij ten obiekt
														// zmienia przekazaną "macierz" na pustą
	// ... wykonaj obliczenia

	// po zakończeniu nie będzie wcale obiektu matrix
}


void AcceptAndProcessMatrix( unique_ptr< TMatrix > matrix )
{
	// jeśli tutaj, wówczas obiekt TMatrix zarządzany jest przez 
	// lokalny unique_ptr dla matrix ‐ funkcja jest w jego posiadaniu

	assert( matrix );


	// ... wykonaj obliczenia

	// po wyjściu nie będzie już wcale obiektu matrix
}


void unique_ptr_OrphanAcceptTest( void )
{
	auto	matrix_1( OrphanRandomMatrix( 20, 20 ) );
	// matrix_1 jest typu unique_ptr< TMatrix >

	assert( matrix_1 );		// pewnij się, że obiekt został utworzony (wystarczająca pamięć itd.)

	cout << "Det = " << ComputeDeterminant( * matrix_1 ) << endl;


	double determinant {};
	bool detCompStatus = ComputeDeterminant( matrix_1, determinant );

	assert( detCompStatus );


	TakeOverAndProcessMatrix( matrix_1 );		// spowoduje to przejęcie obiektu TMatrix z przekazanego unique_ptr
	//TakeOverAndProcessMatrix( & matrix_1 );		// spowoduje to przejęcie obiektu TMatrix z przekazanego unique_ptr

	assert( ! matrix_1 );		// brak obiektu, tylko pusty wskaźnik unique_ptr


	matrix_1 = make_unique< TMatrix >( 20, 20 );	// utwórz inny świeży obiekt (semantyka przenoszenia)

	assert( matrix_1 );

	//AcceptAndProcessMatrix( matrix_1 );	// generuje błąd ‐ "próba odwołania do usuniętej funkcji"
	AcceptAndProcessMatrix( move( matrix_1 ) );	// musimy użyć semantyki przenoszenia

	assert( ! matrix_1 );		// brak obiektu, tylko pusty wskaźnik unique_ptr

	AcceptAndProcessMatrix( OrphanRandomMatrix( 20, 20 ) );		// możemy również utworzyć i przekazać obiekt tymczasowy

}



/////////////////////////////////////////////////////////////////////



void shared_ptr_test( void )
{

	auto sp_0 = make_shared< AClass >( "Hold by shared" );	// a control block will be created

	assert( sp_0 );			// sp_0 cast to bool to check if it is not empty
	assert( sp_0.get() != nullptr );			// the same

	auto sp_1 = sp_0;		// copy for shared is OK - now both point at the same
							// object, one control block, and the reference counter is 2


	cout << sp_0->GetStr() << " = " << (*sp_1).GetStr() << endl;	// accessing the same object
	cout << "sp_0 count = " << sp_0.use_count() << ", sp_1 count = " << sp_1.use_count() << endl;

	sp_0.reset();
	cout << "after reset sp_0 count = " << sp_0.use_count() << ", sp_1 count = " << sp_1.use_count() << endl;



	//---------------------------------------------------
	// shared_ptr can be made out of the unique_ptr

	auto up_0 = make_unique< AClass >( "Created by unique" );

	shared_ptr< AClass > sp_2 = move( up_0 ); 

	auto sp_3 = sp_2;

	cout << sp_2->GetStr() << " = " << (*sp_3).GetStr() << endl;	// accessing the same object
	cout << "sp_2 count = " << sp_2.use_count() << ", sp_3 count = " << sp_3.use_count() << endl;


	//---------------------------------------------------
	// shared_ptr to an array

	const int kElems = 8;
	shared_ptr< AClass [] >	sp_4( new AClass[ kElems ] );
	
	cout << "sp_4 count = " << sp_4.use_count() << endl;

	for( int i = 0; i < kElems; ++ i )
		cout << sp_4[ i ].GetStr() << ", ";

	cout << endl;

	shared_ptr< AClass [] >	sp_5( sp_4 );
	cout << "sp_4 count = " << sp_4.use_count() << ", sp_5 count = " << sp_5.use_count() <<  endl;

}


using shared_ptr_2_buffer = shared_ptr< AClass [] >;

void acceptor_0( shared_ptr_2_buffer sh, const int num_of_elems )
{
	cout << "sh.use_count() = " << sh.use_count() << endl;

	// Work with data ...
	if( num_of_elems > 2 )
		cout << sh[ 2 ].GetStr() << endl;

}

void acceptor_1( shared_ptr_2_buffer sh, const int num_of_elems )
{
	cout << "sh.use_count() = " << sh.use_count() << endl;

	// Work with data ...
	if( num_of_elems > 3 )
		cout << sh[ 3 ].GetStr() << endl;


	acceptor_0( sh, num_of_elems );
}



void donator( void )
{
	const int kBufLen = 4;
	shared_ptr_2_buffer	sh( new AClass[ kBufLen ] );

	for( auto i : range( kBufLen ) )
		sh[ i ].SetStr( to_string( i ) );	// init, from numbers to strings
	
	cout << "sh.use_count() = " << sh.use_count() << endl;

	// Share the buffer with other functions

	acceptor_1( sh, kBufLen );

	// Work with data ...


	cout << "sh.use_count() = " << sh.use_count() << endl;

}


///////////////////////////////////////////////////////////////////////////
// weak_ptr test

class N
{
	string fStr;  // dane własne
public:	
	const string & GetStr( void ) const { return fStr; }
	void SetStr( const string & s ) { fStr = s; }

private:	
	shared_ptr< N > fNext;	// połączenie do przodu
	weak_ptr< N >	fPrev;	// połączenie do tyłu

public:	
	void SetNext( shared_ptr< N > s ) { fNext = s; }
	//void SetPrev( weak_ptr< N >	p ) { fPrev = p; }
	shared_ptr< N > GetNext( void ) const { return fNext; }
public:		
	// Domyślny/parametryczny konstruktor
	N( const string & s = "", const shared_ptr< N > & prev = nullptr ) : fStr( s ), fPrev( prev ) {}
	~N() { cout << "Killing node " << fStr << endl; }

public:	
	// Dodaje 3 teksty... <‐> [i‐1] <‐> [i] <‐> [i+1] <‐> ...
	string operator() ( void )
	{
		string outStr;

		// fPrev jest wskaźnikiem weak_ptr – najpierw sprawdź, czy jest prawidłowy
		if( fPrev.expired() == false ) outStr += fPrev.lock()->GetStr();
		outStr += fStr;
		// fNext jest wskaźnikiem shared_ptr – również sprawdź, czy jest prawidłowy
		if( fNext ) outStr += fNext->GetStr();

		return outStr;
	}
};




void double_linked_list_test( void )
{
	using SP_N = shared_ptr< N >;	// przydatny alias typu
	

	SP_N root, pr;		// dwa puste wskaźniki współdzielone

	// ---------------
	// Utwórz listę
	for( const auto & s : { "A", "B", "C", "D", "E", "F" } )
	{
		if( ! pr /*== false*/ )
		{
			root = pr = make_shared< N >( s );	// pierwszy węzeł
		}
		else
		{
			// Utwórz nowy węzeł i podłącz do poprzedniego węzła na liście
			pr->SetNext( make_shared< N >( s, pr ) );
			pr = pr->GetNext();		// Przesuń pr na koniec listy
		}
	}

	// ---------------------------------------------------------------
	// Ok, lista jest gotowa, więc przejdź po liście i wywołaj operator()
	// Aby sprawdzić, czy pokazuje na prawidłowy obiekt, niejawnie użyj operatora bool ()
	//                  v
	for( SP_N p = root; p; p = p->GetNext() )
		cout << ( * p )() << endl;
}

// Pass shared_ptr by value to create another link to an object
void ProcessObject_0( shared_ptr< AClass > sp )
{
	cout << "sp.use_count = " << sp.use_count() << endl;

	// do something with sp ...

	sp.reset();	// sp is local to this function

	cout << "sp.use_count = " << sp.use_count() << endl;
}

// Pass shared_ptr by a reference to change that shared_ptr
void ProcessObject_1( shared_ptr< AClass > & sp )
{
	cout << "sp.use_count = " << sp.use_count() << endl;

	// do something with sp ...

	sp.reset();	// sp is local to this function

	cout << "sp.use_count = " << sp.use_count() << endl;
}

void weak_ptr_test( void )
{
	auto sp_0 = make_shared< AClass >( "Goose" );
	cout << "sp_0 created" << endl;

	cout << "\tsp_0.use_count = " << sp_0.use_count() << endl;

	weak_ptr< AClass > wp_0( sp_0 ); // create a weak_ptr assoc with sp_0
	cout << "wp_0 created" << endl;

	auto sp_1 = sp_0;
	cout << "sp_1 created" << endl;

	cout << "\tsp_0.use_count = " << sp_0.use_count() << endl; // there is one 
	cout << "\tsp_1.use_count = " << sp_1.use_count() << endl; // control block

	// Check if the object is still alive
	if( wp_0.expired() != true )
	{
		// We can access the object via lock()
		cout << wp_0.lock()->GetStr() << endl;
	}

	assert( sp_0 );	// assert that the main object is OK

	cout << sp_0->GetStr() << endl;	// main object still OK

	cout << "sp_0.reset()" << endl;
	sp_0.reset();	// detach sp_0

	cout << "\tsp_0.use_count = " << sp_0.use_count() << endl; // there is one 
	cout << "\tsp_1.use_count = " << sp_1.use_count() << endl; // control block
	cout << ( wp_0.expired() ? "\twp_0 expired" : "\twp_0 not expired" ) << endl;

	cout << "wp_0.reset()" << endl;
	wp_0.reset();	// detach (only) wp_0 from the control block 
						// - does not affect the held object

	assert( sp_1 );	// assert that the main object is OK but through sp_1
	cout << sp_1->GetStr() << endl;	// use the main object via sp_1


	cout << "\tsp_0.use_count = " << sp_0.use_count() << endl; 
	cout << "\tsp_1.use_count = " << sp_1.use_count() << endl; 
	cout << ( wp_0.expired() ? "\twp_0 expired" : "\twp_0 not expired" ) << endl;

	cout << "sp_1.reset()" << endl;	
	sp_1.reset();	// detach sp_1


	cout << "\tsp_0.use_count = " << sp_0.use_count() << endl; 
	cout << "\tsp_1.use_count = " << sp_1.use_count() << endl; 
	cout << ( wp_0.expired() ? "\twp_0 expired" : "\twp_0 not expired" ) << endl;


	//ProcessObject_0( sp_0 );

	//ProcessObject_1( sp_0 );

}




// -----------------------------------------------------------------



// Cyclic dependence problem

struct Bar;

struct Foo
{
	std::shared_ptr< Bar > bar;
	~Foo() { std::cout << "~Foo()\n";}
};

struct Bar
{
	std::shared_ptr< Foo > foo; // Here we have a problem ... 
	//std::weak_ptr< Foo > foo; // A solution
	~Bar() { std::cout << "~Bar()\n";}
};

void CyclicPointersProblem_Test( void )
{
	auto foo = make_shared< Foo >();
	foo->bar = make_shared< Bar >();

	foo->bar->foo = foo;	// oops, a circle ...
}













