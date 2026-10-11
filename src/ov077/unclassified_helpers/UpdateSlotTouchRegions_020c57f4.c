#include "nitro/types.h"

typedef struct {
    s32 x;
    s32 y;
    BOOL enabled;
    u8 pad_0c[0xc];
} TouchRegion;

typedef struct {
    u8 pad_00000[0x11ed4];
    TouchRegion regions[12];
    s32 mode;
    s32 slot;
    u8 pad_11ffc[4];
    s32 busy;
} MenuWork;

extern BOOL func_ov039_020bc0d4(void);

static inline BOOL IsTouchLocked(void)
{
    return func_ov039_020bc0d4() == FALSE;
}

void UpdateSlotTouchRegions_020c57f4(MenuWork *work, BOOL shifted)
{
    TouchRegion *region;
    int x;
    int slot;
    int i;
    int y;

    work->regions[7].enabled = (work->busy == 0 && work->mode != 1);
    work->regions[8].enabled = FALSE;
    work->regions[9].enabled = FALSE;
    work->regions[10].enabled = FALSE;
    work->regions[11].enabled = FALSE;
    if (shifted) {
        if (work->slot < 2) {
            work->regions[9].enabled = TRUE;
        } else {
            work->regions[11].enabled = TRUE;
        }
    } else {
        if (work->slot < 2) {
            work->regions[8].enabled = TRUE;
        } else {
            work->regions[10].enabled = TRUE;
        }
    }
    slot = work->slot;
    x = (slot == 1 ? 8 : 0) + 0x58;
    y = slot * 16 + 0x30 + (slot >= 2 ? 0x18 : 0);
    for (i = 0; i < 12; i++) {
        switch (i) {
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            region = &work->regions[i];
            region->x = x;
            region->y = y;
            break;
        }
    }
    if (IsTouchLocked()) {
        work->regions[7].enabled = FALSE;
    }
}


















