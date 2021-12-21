#include "gauss.h"
#include <stdio.h>

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
	int wiersze = mat->r;
	int kolumny = mat->c;
	for(int i = 0; i < kolumny; i++) {
		if(mat->data[i][i] == 0) {
//		printf("Macierz osobliwa\n");
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

