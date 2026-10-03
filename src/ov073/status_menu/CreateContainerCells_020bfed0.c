#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

extern s16 PXI_Init_0204f0b4(ResourceContainer *container, int cellId, int flags);
extern void func_0204f2e4(ResourceContainer *container, int cellIndex);

void CreateContainerCells_020bfed0(ResourceContainer *container, s16 *cells, int cellId, int count)
{
    int i = 0;

    do {
        *cells = PXI_Init_0204f0b4(container, cellId, 0);
        func_0204f2e4(container, *cells);
        cells++;
    } while (++i < count);
}
