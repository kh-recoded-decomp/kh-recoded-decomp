#include "nitro/types.h"
#include "nitro/hw.h"

typedef struct PanelState {
    u64 savedTick;
    u32 savedValue;
    u8 pad_0C[0x80];
    s32 streamOffset;
    u8 pad_90[0x24];
    s32 confirmed;
    u8 pad_B8[0x8];
    s32 fadeEngine;
    s32 fadePending;
} PanelState;

extern PanelState *g_ptr_0205fe24;
extern u8 data_02055f54[];

extern s32 func_ov001_02063a38(void);
extern void OS_SetTick_02004084(u64 count);
extern u32 func_02001194(u32 value);
extern void func_0204da20(int arg0);
extern void StartSoundStreamAtOffset_0204df50(int handleIndex, u32 offset);
extern void FadeBgmVolume_0204d9a8(int targetVolume, int frames);
extern void InvokeForChannelOrBoth_0200110c(u32 arg0, u32 arg1, int arg2, int channel);
extern BOOL IsSoundStreamActive_0204ded4(int handleIndex);
extern void StopSoundStreamAtIndex_0204deb0(int handleIndex, int fadeFrame);
extern void func_020281cc(void);

static inline void SetVisiblePlane(int plane)
{
    *(vu32 *)REG_DISPCNT_ADDR = (*(vu32 *)REG_DISPCNT_ADDR & ~0x1f00) | (plane << 8);
}

BOOL ClosePanelAndResume_0202874c(void)
{
    PanelState *panel = g_ptr_0205fe24;

    if (func_ov001_02063a38() != 8) {
        SetVisiblePlane(1);
    } else {
        SetVisiblePlane(3);
    }
    OS_SetTick_02004084(panel->savedTick);
    func_02001194(panel->savedValue);
    func_0204da20(0);
    if (panel->confirmed == 0 && panel->streamOffset != -1) {
        StartSoundStreamAtOffset_0204df50(0, panel->streamOffset);
    }
    FadeBgmVolume_0204d9a8(0x7f, 10);
    panel->streamOffset = -1;
    if (panel->confirmed == 0) {
        panel->fadePending = 1;
        InvokeForChannelOrBoth_0200110c(1, (u32)data_02055f54, (int)func_020281cc, -1);
    } else {
        panel->fadeEngine = 3;
        if (IsSoundStreamActive_0204ded4(0)) {
            StopSoundStreamAtIndex_0204deb0(0, 0);
        }
    }
    panel->confirmed = 0;
    return TRUE;
}
