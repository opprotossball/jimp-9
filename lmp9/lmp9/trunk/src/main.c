#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include "test.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char ** argv) {
	if (strcmp(argv[1], "test")==0) {
		test("A1", "b1", "W1", "O1");
		test("A2", "b2", "W2", "O2");
		test("A3", "b3", "W3", "O3");
		test("A4", "b4", "W4", "O4");
		test("A5", "b5", "W5", "O5");
		
		return 0;
	}
	int res;
	Matrix * A = readFromFile(argv[1]);
	Matrix * b = readFromFile(argv[2]);
	Matrix * x;

	if (A == NULL) return -1;
	if (b == NULL) return -2;
	printToScreen(A);
	printToScreen(b);

	res = eliminate(A,b);
	if (res != 0) {
		if (res == 1){
			printf("Macierz osobliwa\n");
			return -2;
			}
		printf("Układ sprzeczny\n");
		return -3;
	}
	x = createMatrix(b->r, 1);
	if (x != NULL) {
		res = backsubst(x,A,b);
		if (res == 2)
			fprintf(stderr,"Błąd! Nieprawidłowe rozmiary macierzy.\n");
		else if (res == 1)
			fprintf(stderr,"Błąd! Dzielenie przez 0.\n");
		else
			printToScreen(x);
      	 	freeMatrix(x);
	} else {
		fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
	}

	freeMatrix(A);
	freeMatrix(b);

	return 0;
}
