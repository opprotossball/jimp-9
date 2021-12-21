#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

//Wartosc bezwzgledna
double bezwzgl(double x);

/**
* Wyznaczanie najwiekszego wspolczynnika
* w danej kolumnie i zamiana wierszy
*/
void met_najw_elem(Matrix *mat, Matrix *b, int i);

/**
* Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b);

#endif
