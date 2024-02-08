#ifndef SOLVER_H
#define SOLVER_H

#include <Grid.h>

/**
 * Applies the rules #1, 2 and 3 of the Sudoku Solving process.
 * 
 * @param grid : the sudoku grid
 * 
 * @return A boolean indicating wether the grid changed or not 
 * 
 * @author Baptiste
 */
bool removeNotesInGridByZones(T_Grid grid);


/**
 * Applies rules 5 to 10 of the Sudoku Solving process.
 * 
 * @param grid : the sudoku grid
 * @param k : the number of element in the k-uplet
 * 
 * @return A boolean indicating wether the grid changed or not
 * 
 * @author Marie
 */
bool kUpletsSolve(T_Grid grid, const int k, FILE* output_file);

void writeInDoc(int** coordsTuple, int* variable, FILE* outputFile, const char* info1, const char* info2, int k, unsigned char** noteRemoved, int** coordsNoteRemoved);

#endif