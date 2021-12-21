
#include <stdlib.h>
#include "mat_io.h"
#include "test.h"
#include "gauss.h"
#include "backsubst.h"


int test_count=0;
FILE *out;

int run(char *Macierz, char *Wspolczynniki) {
	Matrix * A = readFromFile(Macierz);
	Matrix * b = readFromFile(Wspolczynniki);
	Matrix * x;
	if (A == NULL) {
		return -1;
	}
	if (b == NULL) {
		return -2;
	}
	FILE *out = fopen("out", "w");   //plik do którego zapisywany jest wynik działania programu
	
	int res;
	res = eliminate(A,b);
	if (res != 0) {
		if (res == 1) {
			fprintf(out,"Macierz osobliwa\n");
		}else{
		fprintf(out,"Układ sprzeczny\n");
		}
	}else{
		x = createMatrix(b->r, 1);
		if (x != NULL) {
			res = backsubst(x,A,b);
			if (res == 2)
				fprintf(out,"Błąd! Nieprawidłowe rozmiary macierzy.\n");
			else if (res == 1)
				fprintf(out,"Błąd! Dzielenie przez 0.\n");
			else {
				printToFile(x, out);
				freeMatrix(x);
			}
		} else {
			fprintf(out,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
		}
	}
	fclose(out);
	freeMatrix(A);
	freeMatrix(b);
	return 0;
}

int compare(char *Wynik, char *Out) {
	FILE *wynik = fopen(Wynik, "r");
	FILE *out = fopen(Out, "r");
	char chw, cho;
	chw = fgetc(wynik);
	cho = fgetc(out);
	while (chw != EOF && cho != EOF) {
		if (chw != cho){ 
               		 return -1;
		}
		chw = fgetc(wynik);
		cho = fgetc(out);
	}
	if (chw == EOF && cho == EOF)
        return 0;
    else
        return -1;
}

int test(char *Macierz, char *Wspolczynniki, char *Wynik, char *Opis) {
	test_count++;
	if (run(Macierz, Wspolczynniki)==0) {
		printf("Test %d - ", test_count);
			char c;
			FILE *opis = fopen(Opis, "r");
			c = fgetc(opis);
			printf("%c", c);
			while (c != EOF && c != '\n') {
				c = fgetc(opis);
				printf("%c", c);
			}
			fclose(opis);
		if (compare(Wynik, "out") == 0) {
			printf("  OK\n");
		}else{
			printf("   Wystąpił błąd!\n");
		}
	}
}


