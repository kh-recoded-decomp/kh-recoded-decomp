#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0x98];
    u8 panel[0xc9ac - 0x98];
    u8 entryTable[0xcb90 - 0xc9ac];
    u8 *entryIds;
    u8 pad_cb94[0xcf2c - 0xcb94];
    u8 groupCounts[0x10];
    u8 extraCount;
    u8 pad_cf3d[3];
    s16 groupSelections[0x1a];
    s16 group;
    u8 pad_cf76[2];
    s16 index;
    u16 groupWidth;
    s16 selection;
    s16 count;
} PanelState;

extern PanelState *g_panelState_0206f9a0;
extern u8 data_ov014_0206f7fc[];
extern void *func_ov027_020b90a4(void *panel, int slot);
extern void func_ov027_020b91c8(void *panel, void *record, void *buffer, int flag);
extern void func_ov027_020b96a0(void *panel, void *record, u16 mode);
extern void func_ov014_0206f0a0(void);
extern int func_ov002_02069504(void *table, int entry, int flag);

static inline void ShowPanelGroup(void *panel, int group)
{
    s32 frame[2];
    void *record = func_ov027_020b90a4(panel, 2);
    frame[0] = (group * 3) << 16;
    func_ov027_020b91c8(panel, record, frame, 4);
    record = func_ov027_020b90a4(panel, 3);
    func_ov027_020b96a0(panel, record, group);
}

BOOL SelectPanelEntry_0206f230(int entry)
{
    int group;
    int index;
    s16 oldGroup = g_panelState_0206f9a0->group;
    s16 oldIndex = g_panelState_0206f9a0->index;
    s16 oldSelection = g_panelState_0206f9a0->selection;

    if (entry < 6) {
        index = entry;
        group = 0;
    } else if (entry < 11) {
        index = entry - 6;
        group = 1;
    } else if (entry < 17) {
        index = entry - 11;
        group = 2;
    } else if (entry == 17) {
        group = 3;
        index = 0;
    } else if (entry < 20) {
        index = 6;
        group = 2;
    } else {
        index = 5;
        group = 2;
    }
    g_panelState_0206f9a0->group = group;
    ShowPanelGroup(g_panelState_0206f9a0->panel, group);
    g_panelState_0206f9a0->index = index;
    g_panelState_0206f9a0->groupWidth = data_ov014_0206f7fc[group];
    func_ov014_0206f0a0();

    if (entry < 20 && entry != 16) {
        g_panelState_0206f9a0->count = g_panelState_0206f9a0->groupCounts[entry];
        g_panelState_0206f9a0->selection = g_panelState_0206f9a0->groupSelections[entry];
    } else {
        int i = 0;
        int id = func_ov002_02069504(g_panelState_0206f9a0->entryTable, entry, i);
        if (id >= 0) {
            g_panelState_0206f9a0->count = g_panelState_0206f9a0->extraCount;
            for (; i < g_panelState_0206f9a0->count; i++) {
                if (id == g_panelState_0206f9a0->entryIds[i]) {
                    g_panelState_0206f9a0->selection = i;
                    break;
                }
            }
        }
    }
    return oldGroup != g_panelState_0206f9a0->group || oldIndex != g_panelState_0206f9a0->index ||
           oldSelection != g_panelState_0206f9a0->selection;
}
