#include "nitro/types.h"

struct Ov008SubitemBlock;

extern void *g_panelState_02074ce0;
extern void *func_ov027_020b90a4(void *panel, int id);
extern void ApplySelectedSubitemValues_020b94fc(int target, struct Ov008SubitemBlock *obj, s32 useAlt);

void func_ov013_02070e40(s32 useAlt) {
    u8 *state;
    void *panel;
    void *obj;

    state = (u8 *)g_panelState_02074ce0;
    panel = state + 0x6818;
    obj = func_ov027_020b90a4(panel, 0x14);
    ApplySelectedSubitemValues_020b94fc((int)panel, obj, useAlt);

    state = (u8 *)g_panelState_02074ce0;
    panel = state + 0x6818;
    obj = func_ov027_020b90a4(panel, 0x15);
    ApplySelectedSubitemValues_020b94fc((int)panel, obj, useAlt);

    state = (u8 *)g_panelState_02074ce0;
    panel = state + 0x6818;
    obj = func_ov027_020b90a4(panel, 0x16);
    ApplySelectedSubitemValues_020b94fc((int)panel, obj, useAlt);

    state = (u8 *)g_panelState_02074ce0;
    panel = state + 0x6818;
    obj = func_ov027_020b90a4(panel, 0x17);
    ApplySelectedSubitemValues_020b94fc((int)panel, obj, useAlt);

    state = (u8 *)g_panelState_02074ce0;
    panel = state + 0x6818;
    obj = func_ov027_020b90a4(panel, 0x18);
    ApplySelectedSubitemValues_020b94fc((int)panel, obj, useAlt);

    state = (u8 *)g_panelState_02074ce0;
    panel = state + 0x6818;
    obj = func_ov027_020b90a4(panel, 0x19);
    ApplySelectedSubitemValues_020b94fc((int)panel, obj, useAlt);

    state = (u8 *)g_panelState_02074ce0;
    panel = state + 0x6818;
    obj = func_ov027_020b90a4(panel, 6);
    ApplySelectedSubitemValues_020b94fc((int)panel, obj, useAlt);
}
