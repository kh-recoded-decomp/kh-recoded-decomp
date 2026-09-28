#include "nitro/types.h"

typedef struct {
    s32 status : 8;
    u32 statusHigh : 24;
    u8 pad_04[0x382c];
} SaveSlot;

typedef struct {
    u8 slotIndex;
    u8 pad_01;
    u8 needsRedraw;
    u8 pad_03;
    s32 step : 8;
    u32 stepHigh : 24;
    u8 unk_08;
    u8 pad_09[2];
    u8 unk_0B;
    u8 pad_0C[0x6c];
    SaveSlot slots[2];
} SaveSelectScreen;

extern u32 func_ov039_020bc914(void);
extern int func_02025658(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void ConfirmSelectedSlot_020c5cb4(SaveSelectScreen *screen)
{
    if (func_ov039_020bc914() == 3 && func_02025658() == 1 && screen->step == 0) {
        if (screen->slots[screen->slotIndex].status != 0) {
            screen->step = 1;
            screen->unk_0B = 1;
            screen->unk_08 = 1;
            screen->needsRedraw = 1;
            PlaySoundEffect_0204d924(0, 1);
            return;
        }
        PlaySoundEffect_0204d924(0, 4);
    }
}
