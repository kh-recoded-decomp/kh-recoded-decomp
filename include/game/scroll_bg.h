#ifndef RECODED_SCROLL_BG_H
#define RECODED_SCROLL_BG_H

#include "nitro/types.h"

typedef struct ScrollBgTransfer {
    u32 paletteTask;
    u32 characterTask;
    u32 screenTask;
    u32 paletteSlot;
} ScrollBgTransfer;

typedef struct ScrollBgTransfers {
    ScrollBgTransfer layers[4];
} ScrollBgTransfers;

typedef char ScrollBgTransferSizeCheck[(sizeof(ScrollBgTransfer) == 16) ? 1 : -1];
typedef char ScrollBgTransfersSizeCheck[(sizeof(ScrollBgTransfers) == 64) ? 1 : -1];

extern const ScrollBgTransfers gScrollTextBackgroundTransfers;

#endif
