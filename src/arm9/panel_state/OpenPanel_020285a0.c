#include "nitro/types.h"

typedef struct PanelSlot {
    s32 timer;
    s32 mode;
} PanelSlot;

typedef struct PanelState {
    u64 openTick;
    u32 openFrame;
    u8 pages[0x68];
    PanelSlot slots[2];
    s32 blinkCounter;
    s32 blinkMode;
    u32 streamCursor;
    u8 pad_90[4];
    s32 selectedSlot;
    s32 field_98;
    u8 pad_9c[8];
    u32 visiblePlanes;
    u32 visibleWindows;
    u8 pad_ac[8];
    s32 field_b4;
    s32 active;
    s32 splitLayout;
    s32 state;
    s32 opened;
} PanelState;

extern PanelState *g_ptr_0205fe24;
extern u8 data_0205fdc4;
extern u8 data_02055f44[];
extern s32 func_ov001_02063a38(void);
extern u64 func_02003fd4(void);
extern u32 func_01ff80d4(void);
extern s32 func_020284e8(void);
extern BOOL IsSoundStreamActive_0204ded4(int handleIndex);
extern u32 GetNextStreamCursorOrInvalid_0204df04(int handleIndex);
extern void StopSoundStreamAtIndex_0204deb0(int handleIndex, int fadeFrame);
extern void func_0204d9a8(int a, int b);
extern void func_01ff8830(void *dst, int value, u32 size);
extern void func_02027eec(void);
extern void InvokeForChannelOrBoth_0200110c(u32 arg0, void *arg1, void *arg2, int channel);

BOOL OpenPanel_020285a0(void)
{
    PanelState *panel = g_ptr_0205fe24;

    if (func_ov001_02063a38() == 9) {
        return FALSE;
    }
    if (data_0205fdc4 == 0) {
        panel->active = 0;
        return FALSE;
    }
    panel->field_98 = 0;
    panel->openTick = func_02003fd4();
    panel->openFrame = func_01ff80d4();
    panel->field_b4 = 0;
    panel->splitLayout = func_020284e8();
    if (IsSoundStreamActive_0204ded4(0)) {
        panel->streamCursor = GetNextStreamCursorOrInvalid_0204df04(0);
        StopSoundStreamAtIndex_0204deb0(0, 0);
    }
    func_0204d9a8(0x40, 10);
    panel->selectedSlot = 0;
    func_01ff8830(&panel->blinkCounter, 0, 8);
    func_01ff8830(panel->slots, 0, 0x10);
    panel->slots[0].mode = 1;
    panel->opened = 1;
    panel->visiblePlanes = (*(vu32 *)0x04000000 & 0x1f00) >> 8;
    panel->visibleWindows = (*(vu32 *)0x04000000 & 0xe000) >> 13;
    InvokeForChannelOrBoth_0200110c(1, data_02055f44, func_02027eec, -1);
    return TRUE;
}
