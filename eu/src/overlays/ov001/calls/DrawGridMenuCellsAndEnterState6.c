#include "nitro/types.h"

extern void DrawGridMenuCells(s32 obj, u32 flag);

void DrawGridMenuCellsAndEnterState6(s32 obj)
{
    DrawGridMenuCells(obj, 0);
    *(u32 *)(obj + 8) = 6;
}
