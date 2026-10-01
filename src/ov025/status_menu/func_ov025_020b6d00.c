#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x90];
    void *cursorCell;
} ListView;

extern void PlaceCellAtListEntry_020b6c68(ListView *list, int entryIndex, void *cell);

void func_ov025_020b6d00(ListView *list, int entryIndex)
{
    PlaceCellAtListEntry_020b6c68(list, entryIndex, list->cursorCell);
}
