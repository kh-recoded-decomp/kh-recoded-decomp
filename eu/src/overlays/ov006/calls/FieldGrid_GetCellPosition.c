#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GridInfo {
    fx32 originX;
    fx32 originZ;
    fx32 cellSize;
    s16 rows;
    s16 columns;
} GridInfo;

extern fx32 FX_Mul(fx32 left, fx32 right);

void FieldGrid_GetCellPosition(
    GridInfo *grid, int row, int column, VecFx32 *out)
{
    fx32 halfRows = grid->rows;
    fx32 rowOffset = row << FX32_SHIFT;
    VecFx32 *position = out;
    fx32 halfColumns;
    fx32 top;
    fx32 left;

    halfRows <<= FX32_SHIFT;
    halfRows >>= 1;
    top = -halfRows;
    halfColumns = grid->columns;
    halfColumns <<= FX32_SHIFT;
    halfColumns >>= 1;
    left = -halfColumns;

    position->x = grid->originX +
                  FX_Mul(left + (column << FX32_SHIFT), grid->cellSize) +
                  (grid->cellSize >> 1);
    position->y = 0;
    position->z = grid->originZ +
                  FX_Mul(top + rowOffset, grid->cellSize) +
                  (grid->cellSize >> 1);
}
