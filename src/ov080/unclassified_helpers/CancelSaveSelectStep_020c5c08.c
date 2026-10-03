#include "nitro/types.h"

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
    u8 pad_0C[8];
    int returnMode;
    int busy;
    int unk_1C;
} SaveSelectScreen;

extern int func_ov039_020bc914(void);
extern void PopStackEntry_020bc8a0(void);
extern void func_ov039_020bbf78(int a, int b, int c);
extern void DecrementBusyCounterIfPositive_02025494(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);

void CancelSaveSelectStep_020c5c08(SaveSelectScreen *screen)
{
    switch (screen->step) {
    case 0:
        if (func_ov039_020bc914() < 2) {
            PopStackEntry_020bc8a0();
            func_ov039_020bbf78(0, -1, 0);
        } else if (screen->returnMode != 0) {
            screen->step = 2;
            screen->unk_08 = 1;
            screen->unk_1C = 1;
        } else {
            func_ov039_020bbf78(-1, -1, 1);
        }
        PlaySoundEffect_0204d924(0, 3);
        break;
    case 1:
    case 2:
        screen->step = 0;
        screen->unk_0B = 0;
        PlaySoundEffect_0204d924(0, 3);
        break;
    case 4:
    case 6:
        if (screen->busy != 0) {
            screen->busy = 0;
            DecrementBusyCounterIfPositive_02025494();
        }
        if (screen->returnMode != 0) {
            func_ov039_020bbf78(-1, -1, 1);
        } else {
            screen->step = 0;
            screen->unk_0B = 0;
        }
        PlaySoundEffect_0204d924(0, 3);
        break;
    }
    screen->needsRedraw = 1;
}
