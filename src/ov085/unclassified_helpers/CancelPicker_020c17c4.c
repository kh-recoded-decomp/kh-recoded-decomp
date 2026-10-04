#include "nitro/types.h"

typedef struct QuantityPicker {
    u8 mode;
    u8 dirty;
    u8 pad2[4];
    u8 swapped;
    u8 pad7;
    int selected;
} QuantityPicker;

extern void PopStackEntry_020bc8a0(void);
extern void func_ov039_020bbf78(int a, int b, int c);
extern void PlaySoundEffect_0204d924(int channel, int id);
extern void func_ov085_020c0b90(QuantityPicker *picker, u8 confirm);

void CancelPicker_020c17c4(QuantityPicker *picker)
{
    switch (picker->mode) {
    case 0:
        PopStackEntry_020bc8a0();
        func_ov039_020bbf78(7, -1, 1);
        PlaySoundEffect_0204d924(0, 3);
        break;
    case 1:
        PlaySoundEffect_0204d924(0, 3);
        func_ov085_020c0b90(picker, 0);
        break;
    case 2: {
        BOOL confirm = FALSE;

        PlaySoundEffect_0204d924(0, 3);
        picker->swapped = 1;
        if (picker->selected == 0) {
            confirm = TRUE;
        }
        func_ov085_020c0b90(picker, confirm);
        break;
    }
    }
}
