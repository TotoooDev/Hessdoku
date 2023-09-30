#include <testSolver.h>











//PREVIOUS TEST



/*
void test_resetWitness()
{
	printf("\n--------------------\n");
	printf("   RESETWITNESS   \n");
	printf("--------------------\n");

	bool witness[9] = { false, true, false, false, true, false, false, false, true };

	printf("\nwitness before : ");
	aff_witness(witness);

	resetWitness(witness);
	printf("\nwitness after : ");
	aff_witness(witness);
	printf("\n");
}


void test_checkingAccuracy() {

	printf("\n--------------------\n");
	printf("   CHECKINGACCURACY   \n");
	printf("--------------------\n");

	T_Grid test_grid = malloc(9 * sizeof(T_Cell**));
	for (int l = 0; l < 9; l++) {
		T_Cell** tempoTabCell = malloc(9 * sizeof(T_Cell*));
		for (int k = 0; k < 9; k++) {
			T_Cell* tempoCell = malloc(sizeof(T_Cell));
			tempoCell->value = 0;
			tempoTabCell[k] = tempoCell;
		}
		test_grid[l] = tempoTabCell;
	}

	printf("\nSudoku (sans erreur) :\n");
	test_grid[0][0]->value = 1;
	test_grid[0][3]->value = 2;
	test_grid[3][1]->value = 3;
	test_grid[3][6]->value = 4;
	test_grid[0][8]->value = 5;
	test_grid[7][1]->value = 6;
	test_grid[8][6]->value = 7;
	test_grid[6][4]->value = 8;
	test_grid[2][7]->value = 9;
	aff_grid(test_grid);
	printf("erreur ? %d (attendu 1)\n", checkingAccuracy(test_grid));

	printf("\nSudoku (avec erreur sur ligne) :\n");
	test_grid[0][2]->value = 2;
	aff_grid(test_grid);
	printf("erreur ? %d (attendu 0)\n", checkingAccuracy(test_grid));

	printf("\nSudoku (avec erreur sur colonne) :\n");
	test_grid[0][2]->value = 0;
	test_grid[5][3]->value = 2;
	aff_grid(test_grid);
	printf("erreur ? %d (attendu 0)\n", checkingAccuracy(test_grid));

	printf("\nSudoku (avec erreur sur carre) :\n");
	test_grid[5][3]->value = 0;
	test_grid[1][6]->value = 5;
	aff_grid(test_grid);
	printf("erreur ? %d (attendu 0)\n", checkingAccuracy(test_grid));

}

void aff_grid(T_Grid g) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			printf("%d ", g[i][j]->value);
			if ((j + 1) % 3 == 0) {
				printf("| ");
			}
		}
		printf("\n");
		if ((i + 1) % 3 == 0) {
			printf("-----------------------\n");
		}
	}
}

void main_test() {
	printf("\n----------\n");
	printf("   TEST   \n");
	printf("----------\n");

	test_resetWitness();

	test_checkingAccuracy();

	printf("\n");
}
*/