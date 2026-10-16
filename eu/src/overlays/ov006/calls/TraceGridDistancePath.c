#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct GridCell {
    u8 layer;
    u8 distance;
    u16 unknown02;
} GridCell;

typedef struct PathGrid {
    fx32 originX;
    fx32 originZ;
    fx32 cellSize;
    s16 rows;
    s16 columns;
    u32 layer;
    int goalCell;
    int pathLength;
    int unknown1c;
    int *path;
    GridCell *cells;
} PathGrid;

typedef struct GridStep {
    int row;
    int column;
} GridStep;

extern const int sOv006CardinalStepIndices[4];
extern const GridStep sOv006GridSteps[];

void TraceGridDistancePath(PathGrid *grid, int row, int column)
{
    int nextColumn;
    int nextRow;
    int distance;
    int cell;
    int nextCell;
    int i = 0;

    cell = column + row * grid->columns;
    if (grid->cells[cell].distance == 0) {
        return;
    }
    grid->path[grid->pathLength++] = cell;
    do {
        int direction = sOv006CardinalStepIndices[i++];
        int rowStep = sOv006GridSteps[direction].row;
        int columnStep = sOv006GridSteps[direction].column;
        nextRow = row + rowStep;
        nextColumn = column + columnStep;
        nextCell = nextColumn + nextRow * grid->columns;
        if (nextRow < 0 || nextColumn < 0 || nextRow > grid->rows - 1 ||
            nextColumn > grid->columns - 1) {
            continue;
        }
        distance = grid->cells[cell].distance;
        if (distance <= 1) {
            return;
        }
        if (grid->cells[nextCell].distance != 0 &&
            grid->cells[nextCell].distance == grid->cells[cell].distance - 1) {
            grid->path[grid->pathLength++] = nextCell;
            cell = nextCell;
            row = nextRow;
            column = nextColumn;
            i = 0;
        }
    } while (i < 4);
}
