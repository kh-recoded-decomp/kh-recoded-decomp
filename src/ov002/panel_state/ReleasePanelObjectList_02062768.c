#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x10];
    u8 flags_b0 : 4;
    u8 hasListA : 1;
    u8 hasListB : 1;
    u8 flags_b6 : 2;
    u8 pad_11[0xb0 - 0x11];
    u8 listA[0xe4 - 0xb0];
    u8 listB[4];
} PanelState;

extern PanelState *g_panelState_0206c460;
extern void DestroyFndObjectList_020014f0(void *list);

void ReleasePanelObjectList_02062768(int which)
{
    if (which == 0) {
        if (g_panelState_0206c460->hasListA) {
            DestroyFndObjectList_020014f0(g_panelState_0206c460->listA);
        }
        g_panelState_0206c460->hasListA = 0;
    } else {
        if (g_panelState_0206c460->hasListB) {
            DestroyFndObjectList_020014f0(g_panelState_0206c460->listB);
        }
        g_panelState_0206c460->hasListB = 0;
    }
}
