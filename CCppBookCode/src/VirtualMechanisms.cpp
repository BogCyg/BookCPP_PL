// ==========================================================================
//
// Oprogramowanie napisane przez prof. Bogusława Cyganka do użytku z książką:
// ==> Programowanie w języku C++. Wprowadzenie dla inżynierów. PWN 2023 <==
//
// Oprogramowanie jest dostarczane w stanie takim, w jakim jest, i do celów edukacyjnych
// bez żadnych gwarancji ani odpowiedzialności za jego użycie w jakiejkolwiek aplikacji.
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


#include <cassert>
#include <string>
#include <vector>
#include <iostream>
#include <memory>


using std::cout, std::endl;
using std::unique_ptr, std::make_unique;



// --------------------------------------------------------


class TCircle
{

private:

	double	fRadius {};	// dane prywatne do przechowywania promienia koła

public:

	// Zadeklarowana jako "const", ponieważ niczego nie zmienia
	double GetRadius( void ) const { return fRadius; }

	// Dzięki prywatnej danej fRadius możemy sprawdzić jej inicjalizację
	void SetRadius( double v ) { assert( v >= 0.0 ); fRadius = v; }

public:	

	// Konstruktor domyślny i parametryczny w jednym
	TCircle( double r = 0.0 ) : fRadius( r )
	{
		cout << "Constr TCircle called (@" << this << ")" << endl;
	}

	virtual ~TCircle() // virtual bo będziemy z tej klasy dziedziczyć
	{
		cout << "Destr TCircle called (@" << this << ")" << endl;	
	}

private:

	// Podstawowa wersja GetPi (niezbyt dokładna)
	virtual double GetPi( void ) const 
	{
		cout << "TCircle::pi" << endl;
		return 3.14;
	}

public:

	// Istnieje tylko jedna wersja funkcji ComputeArea
	double ComputeArea( void ) const 
	{
		return GetPi() * fRadius * fRadius;
	}
};


// Nieco bardziej dokładne obliczenia
class PrecCircle : public TCircle
{

public:	

	PrecCircle( double r = 0.0 ) : TCircle( r )
	{
		cout << "Constr PrecCircle called (@" << this << ")" << endl;
	}

	virtual ~PrecCircle()
	{
		cout << "Destr PrecCircle called (@" << this << ")" << endl;	
	}

private:

	// W tej klasie chcemy usprawnić GetPi (zwiększyć precyzję)
	// Umieść override na końcu, pomiń virtual na początku.
	double GetPi( void ) const override
	{
		cout << "PrecCircle::pi" << endl;
		return 3.14159265358979;
	}

};


// Ta funkcja używa polimorfizmu C++ do wypisywania promienia i pola obiektu TCircle
// oraz DOWOLNEGO innego obiekty pochodnego od TCircle.
void PrintInfoFor( const TCircle & circ )
{
	double radius	{ circ.GetRadius() };
	double area		{ circ.ComputeArea() };
	cout << "r=" << radius << " ==> A=" << area << endl;
}

void CircleTest( void )
{

	// ---------------------------------------------------------
	cout << "\nExplicitly define two different objects" << endl;
	cout << "----------------------------------------" << endl;

	{
		TCircle		c1( 1.23 );
		PrintInfoFor( c1 );

		PrecCircle	pc1( 1.23 );
		PrintInfoFor( pc1 );

		// Tutaj usuwamy wszystkie obiekty
	}

	// --------------------------------------------------------------------
	cout << "\nLet's access only through a pointer to the base class" << endl;
	cout << "----------------------------------------------------" << endl;

	{
		using TC_UP = unique_ptr< TCircle >;	// TC_UP jest inteligentnym wskaźnikiem

		TC_UP	c1_ptr( make_unique< TCircle >( 1.23 ) );	// utwórz TCircle na stercie
		PrintInfoFor( * c1_ptr );

		TC_UP	pc1_ptr( make_unique< PrecCircle >( 1.23 ) );	// utwórz TCircle na stercie
		PrintInfoFor( * pc1_ptr );

		// Tutaj usuń wszystkie obiekty
	}




}




// --------------------------------------------------------




namespace CRTP_Test
{

	// ----------------------

	template < typename D >
	class TBaseFor
	{

	public:

		// Brak virtual
		void DAction( void )
		{
			D & deriv_part = static_cast< D & >( * this );

			// Wykonaj akcję na klasie pochodnej, bez względu na to czym jest...
			deriv_part.Work();
		}


	};


	class Derived : public TBaseFor< Derived >
	{
	public:

		// Brak virtual
		void Work( void )
		{
			// Zrób coś specyficznego dla Derived ...
		}

	};

	// Użyj Derived w akcji
	void DerivedTest( void )
	{
		Derived d;
		d.DAction();
	}


	// ----------------------

	template < typename D >
	class TBaseCircle
	{
	private:

		double	fRadius {};

	public:

		double GetArea( void ) const
		{
			return fRadius * fRadius * static_cast< D const & >( * this ).GetPi();
		}

	public:

		TBaseCircle( double r = 0.0 ) : fRadius( r ) {}

	};


	class SimpleCircle : public TBaseCircle< SimpleCircle >
	{
	public:	

		double GetPi( void ) const
		{
			return 3.14;
		}

	public:

		SimpleCircle( double r = 0.0 ) : TBaseCircle< SimpleCircle >( r ) {}


	};

	// Nie pomylmy się i nie napiszmy:
	// class PrecCircle : TBaseCircle< SimpleCircle >
	class PrecCircle : public TBaseCircle< PrecCircle >
	{
	public:	

		double GetPi( void ) const
		{
			return 3.1415926535;
		}

	public:

		PrecCircle( double r = 0.0 ) : TBaseCircle< PrecCircle >( r ) {}
	};



	void StaticPolymorphism_Test( void )
	{

		SimpleCircle sc( 13.13 );

		cout << "A1 = " << sc.GetArea() << endl;
		cout << "sizeof( SimpleCircle ) = " << sizeof( SimpleCircle ) << endl;

		PrecCircle pc( 13.13 );

		cout << "A2 = " << pc.GetArea() << endl;
		cout << "sizeof( PrecCircle ) = " << sizeof( PrecCircle ) << endl;


	}


}



// --------------------------------------------------------


class B
{};

class C : public virtual B
{};

class D : public virtual B
{};

class E : public C, public D	// multiple inheritance - diamond structure
{};




// --------------------------------------------------------


// Area of mixins ...


template < typename Base >
class MMixin : public Base 
{
	// Może używać składowych Base ...
};



struct TDate
{
	int			fDay	{};
	std::string	fMonth	{};
	int			fYear	{};
};


template < typename B >
struct MPrint_Date_US : public B
{
	// Amerykański format daty
	void Print( void )
	{
		std::cout << B::fMonth << "/" << B::fDay << '/' << B::fYear << '\n';
	}
};

template < typename B >
struct MPrint_Date_Eu : public B
{
	// Europejski format daty
	void Print( void )
	{
		std::cout << B::fDay << "/" << B::fMonth << '/' << B::fYear << '\n';
	}
};


void MixinTest( void )
{
	// Alias przydaje się przy domieszkach
	using Date_US = MPrint_Date_US< TDate >;
	using Date_Eu = MPrint_Date_Eu< TDate >;

	Date_US		dus { 9, "Nov", 2019 };
	dus.Print();

	Date_Eu		deu { 9, "Nov", 2019 };
	deu.Print();
}

// --------------------------------------------------------





