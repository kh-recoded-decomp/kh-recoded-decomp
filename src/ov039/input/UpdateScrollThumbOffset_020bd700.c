#include "nitro/types.h"

typedef struct ScrollBar {
    s16 count;
    s16 cursor;
    s16 top;
    u8 thumbOffset;
    u8 pageSize;
    u8 step;
    u8 pad_09[0x2b];
    int total;
    u8 pad_38[4];
    u8 trackStart;
    u8 trackEnd;
} ScrollBar;

void UpdateScrollThumbOffset_020bd700(ScrollBar *bar)
{
    int travel = (bar->trackStart - bar->trackEnd) * 8;
    int limit = (bar->count - bar->pageSize) * bar->step;
    int position = bar->total * travel / limit;
    int alignedTotal = bar->total - bar->total % bar->step;
    int alignedPosition = alignedTotal * travel / limit;

    bar->thumbOffset = position - alignedPosition;
}
