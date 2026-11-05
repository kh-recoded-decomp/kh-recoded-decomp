#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x90];
    void *cursorCell;
} ListView;

extern void PlaceCellAtListEntry(ListView *list, int entryIndex, void *cell);

void SetListCursorEntry(ListView *list, int entryIndex)
{
    PlaceCellAtListEntry(list, entryIndex, list->cursorCell);
}
