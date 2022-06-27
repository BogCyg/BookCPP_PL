

#include <iostream>
#include "range.h"
#include "TheStack.h"




// Częściowo specjalizowana using
template < auto MaxElems >
using StackForInt_VarSize = CppBook::TStackFor< int, MaxElems >;

// Pełna klasa
using StackForInt = StackForInt_VarSize< 256 >;


using std::cout, std::endl;



void TheStackTest( void )
{
	StackForInt theStackForInt;

	cout << "\nValues pushed to the stack:\n";

	// // Umieść kolejne wartości
	for( auto a : CppBook::range( 16 ) )
		cout << a << " ", theStackForInt.Push( a );

	cout << "\nContent of the stack:\n";

	// Wypisz zdejmując z góry stosu – for zrobi to wszystko
	for( StackForInt::value_type v {}; theStackForInt.Pop( v ); cout << v << " " )
		;
}



void TheStackTest_2( void )
{


	//////////////////////////////////////////////////////

	// ---------
	class AClass
	{
	private:

		int		fX {};
		long	fY {};
		double	fZ {};

	public:

		AClass( int x = 0, long y = 0, double z = 0.0 ) : fX( x ), fY( y ), fZ( z )
		{}

	};

	using AStack_4_AClass = CppBook::TStackFor< AClass >;
	// ---------


	AStack_4_AClass theStackForAClass;


	AClass obj_1, obj_2;

	// Insert copies of the two objects
	for( int i = 0; i < 10; ++ i )
		theStackForAClass.Push( obj_1 ), theStackForAClass.Push( obj_2 );

	//////////////////////////////////////////////////////


}







