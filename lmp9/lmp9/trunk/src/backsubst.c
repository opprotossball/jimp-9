#include "backsubst.h"
#include <stdio.h>
/*
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	if (!(x->r == b->r && mat->r == x->r && mat->r == mat->c)) //sprawdzenie rozmiarów macierzy
		return 2;
	int wiersze = x->r;
	double sum=0;
	for (int i=wiersze-1; i>-1; i--) {
		if (mat->data[i][i]==0)
			return 1;
			for (int j=wiersze-1; j>i; j--) 
				sum += (x->data[j][0])*(mat->data[i][j]);
		x->data[i][0] = (b->data[i][0] - sum)/mat->data[i][i];
		sum=0;		
	}
	return 0;
}


