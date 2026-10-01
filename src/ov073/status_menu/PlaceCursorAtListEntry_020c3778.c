#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x90];
    void *cursorCell;
} ListView;

extern void PlaceCellAtListEntry_020c36e0(ListView *list, int entryIndex, void *cell);

void PlaceCursorAtListEntry_020c3778(ListView *list, int entryIndex)
{
    PlaceCellAtListEntry_020c36e0(list, entryIndex, list->cursorCell);
}
