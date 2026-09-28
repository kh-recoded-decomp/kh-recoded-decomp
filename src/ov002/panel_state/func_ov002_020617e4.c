#include "nitro/types.h"

typedef struct DispatchEntry {
    u8 pad_00[8];
    void (*action)(void);
    u8 pad_0c[4];
} DispatchEntry;

typedef struct PanelState {
    u8 pad_00[8];
    s32 dispatchIndex;
    u8 pad_0c[4];
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

void func_ov002_020617e4(void) {
    if (g_panelState_0206c460->busy == 1) {
        return;
    }
    g_panelState_0206c460->busy = 1;
    if (g_panelState_0206c460->dispatchReady) {
        void (*action)(void) = g_dispatchTable_0206c2f0[g_panelState_0206c460->dispatchIndex].action;
        if (action != NULL) {
            action();
        }
    }
    g_panelState_0206c460->busy = 0;
}
