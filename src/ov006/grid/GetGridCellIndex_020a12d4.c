#include "nitro/types.h"

typedef struct {
    s32 originX;
    s32 originZ;
    s32 cellSize;
    s16 rows;
    s16 columns;
} GridInfo;

extern int func_02023dbc(int numerator, int denominator);

int GetGridCellIndex_020a12d4(GridInfo *grid, s32 *position)
{
    s16 columns = grid->columns;
    s32 cellSize = grid->cellSize;
    int column = func_02023dbc(position[0] - (grid->originX - ((columns * cellSize) >> 1)), cellSize);
    int row = func_02023dbc(position[2] - (grid->originZ - ((grid->rows * cellSize) >> 1)), cellSize);
    return column + row * columns;
}
