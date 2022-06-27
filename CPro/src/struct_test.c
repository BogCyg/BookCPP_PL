/*

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

*/


#include <stdlib.h>
#include <stdio.h>



/* Prosta struktura do przechowywania współczynników równania kwadratowego */
struct QE
{
	float a, b, c;
};

/* struktura QE jest znacznikiem, a my musimy wprowadzić typ QE */
/* Nazwa struktury jest znacznikiem zamiast typem. */
typedef		struct QE			QE;




/* Zainicjalizuj QE wartością 0 */
void Init_0( QE * qe )
{
	qe->a = 0.0;
	qe->b = 0.0;
	qe->c = 0.0;
}

/* Zainicjalizuj QE wartościami */
void Init( QE * qe, float a, float b, float c )
{
	qe->a = a;
	qe->b = b;
	qe->c = c;
}




/* Oblicza wyróżnik równania kwadratowego */
float ComputeDelta( QE * qe )
{
	return qe->b * qe->b - 4.0 * qe->a * qe->c;
}



/* Funkcja do testowania zachowania struktury QE */
void Test_QE( void )
{
	/* Obiekty te nie są inicjalizowane */
	QE		eq_1;
	QE		eq_2;

	/* Zainicjalizuj eq_1 wartością 0 */
	Init_0( & eq_1 );
	Init_0( & eq_2 );


	float a = 0.0, b = 0.0, c = 0.0;

	/* Wczytaj 3 parametry z klawiatury. scanf akceptuje wskaźniki, więc używany jest & */
	scanf( "%f%f%f", & a, & b, & c );

	/* Bezpośrednio ustaw dane składowe eq_2 */
	eq_2.a = a;
	eq_2.b = b;
	eq_2.c = c;

	/* Oblicz wyróżnik */
	float delta = ComputeDelta( & eq_2 );

	/* Wypisz deltę na ekranie */
	printf( "delta=%lf\n", delta );

}







