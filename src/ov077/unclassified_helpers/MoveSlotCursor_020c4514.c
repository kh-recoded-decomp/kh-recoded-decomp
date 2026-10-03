#include "nitro/types.h"

#define PAD_KEY_UP 0x40
#define PAD_KEY_DOWN 0x80

typedef struct {
    u8 pad_00[0xa];
    u16 repeat;
} PadState;

typedef struct {
    u8 pad_0000[0x2c6a];
    u8 extraSlotCount;
} SaveData;

typedef struct {
    u8 pad_00000[0x11ff8];
    s32 slot;
} MenuWork;

extern SaveData *data_0205fe0c;
extern u16 data_02060500;
extern PadState *func_ov039_020bca00(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void ShowSlotHeaderMessage_020c58e0(MenuWork *work);
extern void *func_ov039_020bc1bc(void);
extern void RefreshElementCellAnimation_020c9d34(void *container, int elementId);

void MoveSlotCursor_020c4514(MenuWork *work)
{
    int lastSlot;
    int previous;
    PadState *pad;

    pad = func_ov039_020bca00();
    previous = work->slot;
    lastSlot = data_0205fe0c->extraSlotCount + 2;

    if (pad->repeat & PAD_KEY_UP) {
        if (--work->slot < 0) {
            if (!(data_02060500 & PAD_KEY_UP)) {
                work->slot = 0;
            } else {
                work->slot = lastSlot;
            }
        }
    } else if (pad->repeat & PAD_KEY_DOWN) {
        if (++work->slot > lastSlot) {
            if (!(data_02060500 & PAD_KEY_DOWN)) {
                work->slot = lastSlot;
            } else {
                work->slot = 0;
            }
        }
    }
    if (work->slot != previous) {
        PlaySoundEffect_0204d924(1, 0);
        ShowSlotHeaderMessage_020c58e0(work);
        RefreshElementCellAnimation_020c9d34(func_ov039_020bc1bc(), 0x2a);
    }
}








