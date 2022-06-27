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






// This include is to use the istream and ostream classes
#include <iostream>




///////////////////////////////////////////
// Nasza własna przestrzeń nazw do jednoznacznego
// identyfikowania zawartych w niej klas
///////////////////////////////////////////
namespace CppBook
{


////////////////////////////////////////////
// Klasa do reprezentowania liczb zespolonych
////////////////////////////////////////////
class TComplex
{
	private:

		// Dane składowe powinny być w sekcji prywatnej klasy

		double fRe {};		// część rzeczywista
		double fIm {};		// część urojona

	public:


		///////////////////////////////////////////////////////////
		// Konstruktor domyślny
		///////////////////////////////////////////////////////////
		TComplex( void ) 
			: fRe( 0.0 ), fIm( 0.0 )	// specjalna inicjalizacja danych
		{
			fRe = 0;					// taka inicjalizacja jest możliwa,  
		}								// ale ta powyższa jest lepsza


		///////////////////////////////////////////////////////////
		// Konstruktor parametryczny 
		///////////////////////////////////////////////////////////
		TComplex( double re, double im ) : fRe( re ), fIm( im ) {}
		
		///////////////////////////////////////////////////////////
		// Konstruktor kopiujący – utwórz ten obiekt i ustaw jego stan
		// na taki sam, jak obiekt dostarczony (tj. "c"). 
		// default oznacza skopiuj fRe i fIm z "c".
		///////////////////////////////////////////////////////////
		TComplex( const TComplex & c ) = default;

		///////////////////////////////////////////////////////////
		// rzeciążony operator przypisania – default oznacza kopiowanie 
		// fRe i fIm.
		///////////////////////////////////////////////////////////
		TComplex & operator = ( const TComplex & c ) = default;

		///////////////////////////////////////////////////////////
		// Destruktor nic nie robi, ale zdefiniowany jest jawnie
		///////////////////////////////////////////////////////////
		~TComplex() = default;			

	public:

		///////////////////////////////////////////////////////////
		// Konstruktor konwertujący – pozwala na tworzenie obiektu TComplex
		// z obiektu typu double (tj. jest to konwersja 
		// z double do TComplex).
		///////////////////////////////////////////////////////////
		TComplex( double re ) : fRe( re ), fIm( 0.0 ) {}


	public:

		// Gettery i setery do uzyskiwania dostępu do składowych klasy
		double GetRe( void ) const { return fRe; }	// "const", ponieważ tylko odczytujemy
		double GetIm( void ) const { return fIm; }	// dane, bez zmieniania stanu
		
		void SetRe( double re ) { fRe = re; }		// tutaj zmieniamy stan
		void SetIm( double im ) { fIm = im; }		// więc nie używamy "const"

	public:

		///////////////////////////////////////////////////////////
		// Przeciążony operator porównywania "równości"
		///////////////////////////////////////////////////////////
		bool operator == ( const TComplex & c ) const
		{
			return fRe == c.fRe && fIm == c.fIm;
		}

	public:

		///////////////////////////////////////////////////////////
		// Przeciążone operatory arytmetyczne
		///////////////////////////////////////////////////////////

		// +
		TComplex operator + ( const TComplex & second_op ) const;

		TComplex & operator += ( const TComplex & second_op );


		// -
		TComplex operator - ( const TComplex & second_op ) const;

		TComplex & operator -= ( const TComplex & second_op );


		// *
		TComplex operator * ( const TComplex & second_op ) const;

		TComplex & operator *= ( const TComplex & second_op );


		// dzielenie – może zgłosić wyjątek dzielenia przez zero
		TComplex operator / ( const TComplex & second_op ) const;

		TComplex & operator /= ( const TComplex & second_op );

};


///////////////////////////////////////////////////////////////
// Przeciążone operatory strumieniowania – zawsze poza klasą

std::istream & operator >> ( std::istream & i, TComplex & complex );

std::ostream & operator << ( std::ostream & o, const TComplex & complex );

///////////////////////////////////////////////////////////////

// Zwraca moduł TComplex
double abs( const TComplex & c );

}		// koniec CppBook


/////////////////////////////////////////////////////////



