#include "nitro/types.h"

struct Ov008SubitemBlock;

extern void *data_ov013_02074ce0;
extern void *FindWidgetById(void *panel, int id);
extern void ApplySelectedSubitemValues(int target, struct Ov008SubitemBlock *obj, s32 useAlt);

void func_ov013_02070e40(s32 useAlt) {
    u8 *state;
    void *panel;
    void *obj;

    state = (u8 *)data_ov013_02074ce0;
    panel = state + 0x6818;
    obj = FindWidgetById(panel, 0x14);
    ApplySelectedSubitemValues((int)panel, obj, useAlt);

    state = (u8 *)data_ov013_02074ce0;
    panel = state + 0x6818;
    obj = FindWidgetById(panel, 0x15);
    ApplySelectedSubitemValues((int)panel, obj, useAlt);

    state = (u8 *)data_ov013_02074ce0;
    panel = state + 0x6818;
    obj = FindWidgetById(panel, 0x16);
    ApplySelectedSubitemValues((int)panel, obj, useAlt);

    state = (u8 *)data_ov013_02074ce0;
    panel = state + 0x6818;
    obj = FindWidgetById(panel, 0x17);
    ApplySelectedSubitemValues((int)panel, obj, useAlt);

    state = (u8 *)data_ov013_02074ce0;
    panel = state + 0x6818;
    obj = FindWidgetById(panel, 0x18);
    ApplySelectedSubitemValues((int)panel, obj, useAlt);

    state = (u8 *)data_ov013_02074ce0;
    panel = state + 0x6818;
    obj = FindWidgetById(panel, 0x19);
    ApplySelectedSubitemValues((int)panel, obj, useAlt);

    state = (u8 *)data_ov013_02074ce0;
    panel = state + 0x6818;
    obj = FindWidgetById(panel, 6);
    ApplySelectedSubitemValues((int)panel, obj, useAlt);
}
