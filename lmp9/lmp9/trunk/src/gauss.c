#include "gauss.h"
#include <stdio.h>

//Wartosc bezwzgledna
double bezwzgl(double x) {
	if (x >= 0)
		return x;
	else
		return -x;
}

/**
 * Wyznaczanie najwiekszego wspolczynnika
 * w danej kolumnie i zamiana wierszy
*/
  
void met_najw_elem(Matrix *mat, Matrix *b, int i) {
	double *tmp = mat->data[i];
	int ktory;
	for(int d = i+1; d < mat->r; d++) {
		if( bezwzgl(mat->data[d][i]) > bezwzgl(tmp[i]) ) {
			tmp = mat->data[d];
			ktory = d;
		}
	}

	mat->data[ktory] = mat->data[i];
	mat->data[i] = tmp;
      
	double tmpb = b->data[ktory][0];
	b->data[ktory][0] = b->data[i][0];
	b->data[i][0] = tmpb;

}

                                                                                                    

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
	int wiersze = mat->r;
	int kolumny = mat->c;
	for(int i = 0; i < kolumny; i++) {
		met_najw_elem(mat, b, i);
		if(mat->data[i][i] == 0) {
			printf("Macierz osobliwa\n");
			return 1;
		}
		for(int j = i+1; j < wiersze; j++) {
			double eliminowany = mat->data[j][i];
			double na_przekatnej = mat->data[i][i];
			for(int e = 0; e < kolumny; e++) {
				mat->data[j][e] = mat->data[j][e] - (eliminowany/na_przekatnej)*mat->data[i][e];

			
			}
			b->data[j][0] = b->data[j][0] - (eliminowany/na_przekatnej)*b->data[i][0];
		}
	}

	return 0;
}

