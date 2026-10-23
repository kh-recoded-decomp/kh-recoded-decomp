#ifndef KH_RECODED_OV080_SAVE_SLOT_H
#define KH_RECODED_OV080_SAVE_SLOT_H

#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x10];
    int bgId;
} SlotFrame;

typedef struct {
    s32 status : 8;
    s32 frameIndex : 8;
    u32 statusHigh : 16;
    u8 pad_04[2];
    s16 emptyElement;
    s16 filledElement;
    u8 pad_0A[2];
    void *cursorElement;
    SlotFrame *frames[5];
    u16 levelText[4];
    u16 moneyText[7];
    u16 playTimeText[10];
    u16 titleText[65];
    u32 saveData[0x3760 / sizeof(u32)];
} SaveSlot;

#endif
