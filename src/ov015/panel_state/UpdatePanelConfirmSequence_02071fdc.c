#include "nitro/types.h"

#define REG_DB_DISPCNT (*(volatile u32 *)0x04001000)

typedef struct PanelState {
    u8 pad_00[0xe4];
    int sequenceStep;
} PanelState;

extern PanelState *data_ov015_0207e960;
extern BOOL func_ov002_0206671c(void);
extern int IsGlobalBit0Set_020632ac(void);
extern BOOL IsButtonBPressed_020632c8(void);
extern u32 GetMenuCursorHeld_02066b84(u32 *out);
extern u32 GetMenuCursorTouch_02066b2c(u32 *out);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_ov002_020620fc(int selector);
extern void func_ov015_02070af8(char nextState);

void UpdatePanelConfirmSequence_02071fdc(void)
{
    BOOL busy = func_ov002_0206671c();

    switch (data_ov015_0207e960->sequenceStep) {
    case 0:
        data_ov015_0207e960->sequenceStep = 5;
        break;
    case 5:
        if (!IsGlobalBit0Set_020632ac() && !IsButtonBPressed_020632c8() && !GetMenuCursorHeld_02066b84(NULL)) {
            break;
        }
        if (IsGlobalBit0Set_020632ac() || GetMenuCursorTouch_02066b2c(NULL)) {
            PlaySoundEffect_0204d924(2, 1);
        } else if (IsButtonBPressed_020632c8()) {
            PlaySoundEffect_0204d924(2, 2);
        }
        func_ov002_020620fc(0);
        REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | 0x1e00;
        data_ov015_0207e960->sequenceStep = 10;
        break;
    case 10:
        if (!busy) {
            data_ov015_0207e960->sequenceStep = 20;
        }
        break;
    case 20:
        func_ov015_02070af8(1);
        break;
    }
}
