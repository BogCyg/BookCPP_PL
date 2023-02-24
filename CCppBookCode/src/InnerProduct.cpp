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




#include <vector>
#include <iostream>
#include <iomanip>
#include <random>
#include <numeric>		// dla iloczynu skalarnego
#include <algorithm>




namespace InnerProducts
{

	using DVec = std::vector< double >;
	using DT = DVec::value_type;
	using ST = DVec::size_type;

	using std::inner_product;
	using std::transform;
	using std::accumulate;
	using std::sort;

	using std::cout, std::endl;

	auto InnerProduct_StdAlg( const DVec & v, const DVec & w )
	{
		// Ostatni argument jest wartością początkową
		return inner_product( v.begin(), v.end(), w.begin(), DT() );
	}


	auto InnerProduct_SortAlg( const DVec & v, const DVec & w )
	{
		DVec z;		// Przechowuje iloczyny poszczególnych elementów

		// Mnożenie poszczególnych elementów: c = v .* w
		transform(	v.begin(), v.end(), w.begin(), 
					back_inserter( z ), 
					[] ( const auto & v_el, const auto & w_el) { return v_el * w_el; } );

		// Posortuj w kolejności rosnącej
		sort( z.begin(), z.end() );		// Czy to magia?
	
		// Ostatni argument jest wartością początkową
		return accumulate( z.begin(), z.end(), DT() );
	}


	// W algorytmie Kahana każde dodawanie korygowane jest przez czynnik korekcji.
	// fW algorytmie tym zakładany jest brak łączności liczb zmiennoprzecinkowych, tj.:
	// ( a + b ) + c != a + ( b + c )
	auto InnerProduct_KahanAlg( const DVec & v, const DVec & w )
	{
		DT theSum {};

		// volatile powstrzymuje kompilator przed stosowaniem jakichkolwiek optymalizacji
		// na obiekcie, ponieważ może on zostać zmieniony przez jakiś zewnętrzny komponent itd.,
		// w sposób, którego kompilator nie jest w stanie przewidzieć.

		volatile DT c {};		// współczynnik "korekcji"

		const ST kElems = std::min( v.size(), w.size() );

		for( ST i = 0; i < kElems; ++ i )
		{
			DT y = v[ i ] * w[ i ] - c;	// Odejmuje czynnik korekcji od y

			DT t = theSum + y;	// Dodaj skorygowany składnik do sumy bieżącej theSum
			// Ale theSum jest duża, zaś y jest małe, więc niższe bity zostaną utracone

			c = ( t - theSum ) - y; // Niższe bity y zostaną utracone podczas sumowania. 
		// Wyższe bity y są obliczane w ramach ( t ‐ theSum ). Następnie, gdy odejmowane jest
		// od tego y, niższe bity y są odzyskiwane (wartość ujemna).
		// Algebraicznie, c zawsze powinno wynosić 0 (uwaga na optymalizacje kompilatora).

			theSum = t;
		}

		return theSum;
	}



	void InnerProduct_Test( void )
	{
		const int kElems = 100000;

		DVec	v( kElems );
		DVec	w( kElems );
	
		std::mt19937		rand_gen{ std::random_device{}() }; 	// Algorytm losowości Mersenne twister

		// ref opakowuje referencję
		std::generate( v.begin(), v.end(), ref( rand_gen ) );
		std::generate( w.begin(), w.end(), ref( rand_gen ) );

		// Podwajamy nasze wektory z użyciem pojedynczego odbicia ujemnego

		// Lambda musi być modyfikowalna, aby umożliwić modyfikację zmiennej n
		v.resize( 2 * kElems );
		std::generate( v.begin() + kElems, v.end(), 
							[ n = 0, & v ] () mutable { return - v[ n ++ ]; } );
		w.resize( 2 * kElems );
		std::generate( w.begin() + kElems, w.end(), 
							[ n = 0, & w ] () mutable { return + w[ n ++ ]; } );

		// Iloczyn skalarny powinien być bliski 0.0, 
		// więc sprawdźmy oba algorytmy.

		cout 	<< "Stand alg error = \t"	<< std::setprecision( 8 ) 
				<< fabs( InnerProduct_StdAlg( v, w ) ) << endl;
		cout 	<< "Sort alg error = \t"	<< std::setprecision( 8 ) 
				<< fabs( InnerProduct_SortAlg( v, w ) ) << endl;
		cout 	<< "Kahan alg error = \t"	<< std::setprecision( 8 ) 
				<< fabs( InnerProduct_KahanAlg( v, w ) ) << endl;
	}

}





