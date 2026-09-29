#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x94];
    s32 selectedSlot;
    u8 pad_98[0x1c];
    s32 confirmed;
    s32 field_b8;
    s32 field_bc;
    u8 pad_C0[0x4];
    s32 fadePending;
} PanelState;

extern PanelState *g_ptr_0205fe24;
extern u32 data_0205fde0;
extern u16 data_02060500;

extern void func_02028188(void);
extern BOOL PlaySoundEffect_0204d924(int seqArcNo, int index);
extern void func_0202819c(void);
extern void func_020283fc(void);
extern void func_020281b4(void);
extern BOOL ToggleSelectedPanelSlot_02028104(void);
extern void func_020284d0(void);
extern void func_0204d980(void);
extern void func_020283bc(int slot);

BOOL UpdatePanelPromptInput_0202867c(void)
{
    PanelState *panel = g_ptr_0205fe24;

    if (data_0205fde0 == 0) {
        return TRUE;
    }
    if (panel->confirmed != 0) {
        func_02028188();
        return TRUE;
    }
    if (panel->field_b8 == 0) {
        PlaySoundEffect_0204d924(0, 3);
        func_0202819c();
        return TRUE;
    }
    if (panel->fadePending == 0) {
        if (data_02060500 & 8) {
            PlaySoundEffect_0204d924(0, 3);
            func_0202819c();
            return TRUE;
        }
        if (panel->field_bc == 0) {
            func_020283fc();
            func_020281b4();
            return TRUE;
        }
        if (!ToggleSelectedPanelSlot_02028104() && (data_02060500 & 1)) {
            if (panel->selectedSlot == 0) {
                func_0202819c();
            } else {
                func_020284d0();
                func_0204d980();
                panel->confirmed = 1;
            }
            PlaySoundEffect_0204d924(0, 1);
            return TRUE;
        }
    }
    func_020283fc();
    func_020283bc(panel->selectedSlot);
    func_020281b4();
    return TRUE;
}
