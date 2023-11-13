#include <Cell.h>
#include <Log.h>
#include <Macros.h>

T_Cell* createCell()
{
    T_Cell* newCell = (T_Cell*)malloc(sizeof(T_Cell));
    if (newCell == NULL) exit(1);

    // Shifts 1 n times and sutracts one to get n times 1
    newCell->notes = (1 << GRID_SIZE) - 1;

    return newCell;
}

void freeCell(T_Cell* cell)
{
    free(cell);
}

void setNoteCell(T_Cell* cell, unsigned int noteValue)
{
    // Set the flag at the specified index to 1 using bitwise OR
    cell->notes |= (1 << (noteValue - 1));
}

bool unsetNoteCell(T_Cell* cell, unsigned int noteValue) {
    unsigned int prevValue = cell->notes;
    // Clear the flag at the specified index by performing a bitwise AND with the complement of the flag
    cell->notes &= ~(1 << (noteValue - 1));
    return cell->notes != prevValue;
}

void setValueOfCell(T_Cell* cell, unsigned int value)
{
    // 
    cell->notes = 0 << (GRID_SIZE - value - 1);
    // We place the bit 
    cell->notes++;
    // And we shift it to its proper location
    cell->notes = cell->notes << (value - 1);
}

static unsigned char isPowerOfTwo(unsigned int n)
{
    return n && (!(n & (n - 1)));
}

unsigned int getValueOfCell(T_Cell* cell)
{
    if (!isPowerOfTwo(cell->notes)) return 0;           // A number's binary representation contains 
                                                        //a single bit set when the number is a power of two
    unsigned i = 1, pos = 1;

    while (!(i & cell->notes))                          // We shift through the bits and stop whenever we find a bit set
    {                                                   // i & cell->notes will be non-zero when i and cell->notes have a set bit at the same position
        i = i << 1;
        ++pos;                                          // We increment the counter, to keep track of our position
    }

    return pos;

}