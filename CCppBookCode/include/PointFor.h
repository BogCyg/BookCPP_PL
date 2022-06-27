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



// Szablonowe składowe w przykładowej klasie szablonowej
template < typename T >
class TPointFor
{

private:

	T	fx {}, fy {};	// Dwie współrzędne typu T


public:

	void Set_x( T x ) { fx = x; }
	void Set_y( T y ) { fy = y; }

	auto Get_x( void ) const { return fx; }
	auto Get_y( void ) const { return fy; }

public:


	// Szablonowy składowy konstruktor kopiujący do inicjalizowania
	// z punktu współrzędnych różnego rodzaju.
	// Aby był ogólny, musi wywoływać Get_x i Get_y
	// Dostęp bezpośredni możliwy tylko, gdy T == U
	template < typename U >
	TPointFor< T >( const TPointFor< U > & pt ) : fx( pt.Get_x() ), fy( pt.Get_y() ) {}

	// Szablonowy składowy operator przypisania do inicjalizowania
	// z punktu współrzędnych różnego rodzaju.
	template < typename U >
	TPointFor< T > & operator = ( const TPointFor< U > & pt )
	{
		//fx = pt.fx;		te dwie linie działają tylko wtedy,
		//fy = pt.fy;		gdy T == U
		fx = pt.Get_x();		// zezwól na konwersję
		fy = pt.Get_y();
		return * this;
	}


	// Konstruktor domyślny musi być jawnie zakodowany, 
	// sponieważ został dodany konstruktor kopiujący i przypisanie
	// (w innym przypadku można go było pominąć).
	//TPointFor( void ) : fx( T() ), fy( T() ) {}
	TPointFor( void ) = default;
};



inline void PointTest( void )
{

	using RealPoint = TPointFor< double >;

	using IntPoint = TPointFor< int >;


	RealPoint rp1, rp2;		// Wywołuje konstruktor domyślny

	IntPoint ip1, ip2;		// Wywołuje konstruktor domyślny

	rp1 = rp2;		// Przypisanie w tej samej klasie
					// - nie jest wymagane specjalne przypisanie szablonowe

	rp1 = ip2;		// Przypisanie między różnymi klasami
					// - konieczne specjalne szablonowe przypisanie

	RealPoint rp3( ip1 );	// Również konstrukcja kopiująca między różnymi klasami
}




