#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 originX;
    fx32 originZ;
    fx32 cellSize;
    s16 rows;
    s16 columns;
} GridInfo;

extern long long func_02023dbc(int numerator, int denominator);
extern void GetGridCellPosition_020a1324(GridInfo *grid, int row, int column, VecFx32 *out);

void GetGridCellCenter_020a1370(GridInfo *grid, int cellIndex, VecFx32 *out)
{
    s16 columns = grid->columns;
    int row = (int)func_02023dbc(cellIndex, columns);
    int column = (int)(func_02023dbc(cellIndex, columns) >> 32);
    GetGridCellPosition_020a1324(grid, row, column, out);
}
