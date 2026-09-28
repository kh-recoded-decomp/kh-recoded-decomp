#include "nitro/types.h"

typedef struct DispatchEntry {
    void (*action)(void);
    u8 pad_04[0xc];
} DispatchEntry;

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 disabled : 1;
    u8 dispatchReady : 1;
    u8 slotAEnabled : 1;
    u8 slotBEnabled : 1;
    u8 slotCEnabled : 1;
    u8 slotDEnabled : 1;
    u8 slotATriggered : 1;
    u8 slotBTriggered : 1;
    u8 slotCTriggered : 1;
    u8 slotDTriggered : 1;
    u8 unk_11_2 : 1;
    u8 busy : 1;
    u8 unk_11_4 : 1;
    u8 unk_11_5 : 1;
    u8 unk_11_6 : 1;
    u8 unk_11_7 : 1;
} PanelState;

extern PanelState *g_panelState_0206c460;
extern DispatchEntry g_dispatchTable_0206c2f0[];
extern u16 data_02060500;

extern void *func_0202a764(void);
extern int func_02004990(void);
extern void func_020273d4(void);
extern int func_0204f5dc(void *p);
extern void func_02001520(void *p);

int func_ov002_0206162c(void) {
    void *rootHeap = func_0202a764();
    int alreadyActive = func_02004990();

    if (alreadyActive == 0) {
        func_020273d4();
    }
    func_0204f5dc((u8 *)rootHeap + 0x12);

    *(u16 *)((u8 *)rootHeap + 0x12) &= 0xf3fc;
    if ((data_02060500 & 1) != 0) {
        *(u16 *)((u8 *)rootHeap + 0x12) |= 1;
    }
    if ((data_02060500 & 2) != 0) {
        *(u16 *)((u8 *)rootHeap + 0x12) |= 2;
    }
    if ((data_02060500 & 0x400) != 0) {
        *(u16 *)((u8 *)rootHeap + 0x12) |= 0x400;
    }
    if ((data_02060500 & 0x800) != 0) {
        *(u16 *)((u8 *)rootHeap + 0x12) |= 0x800;
    }

    g_dispatchTable_0206c2f0[*(s32 *)((u8 *)rootHeap + 8)].action();

    if (g_panelState_0206c460->disabled) {
        return -2;
    }
    if (g_panelState_0206c460->slotAEnabled && g_panelState_0206c460->slotATriggered) {
        func_02001520((u8 *)g_panelState_0206c460 + 0x48);
    }
    if (g_panelState_0206c460->slotBEnabled && g_panelState_0206c460->slotBTriggered) {
        func_02001520((u8 *)g_panelState_0206c460 + 0x7c);
    }
    if (g_panelState_0206c460->slotCEnabled && g_panelState_0206c460->slotCTriggered) {
        func_02001520((u8 *)g_panelState_0206c460 + 0xb0);
    }
    if (g_panelState_0206c460->slotDEnabled && g_panelState_0206c460->slotDTriggered) {
        func_02001520((u8 *)g_panelState_0206c460 + 0xe4);
    }
    g_panelState_0206c460->slotATriggered = 0;
    g_panelState_0206c460->slotBTriggered = 0;
    g_panelState_0206c460->slotCTriggered = 0;
    g_panelState_0206c460->slotDTriggered = 0;
    return 0;
}
