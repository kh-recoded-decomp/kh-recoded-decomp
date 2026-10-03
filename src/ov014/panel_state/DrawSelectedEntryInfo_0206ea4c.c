#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_0000[0xcac0];
    u16 entryName[0x48];
    u8 *groupEntries[0x14];
    u8 pad_cba0[0xcf74 - 0xcba0];
    s16 group;
    u8 pad_cf76[2];
    s16 index;
    u16 groupWidth;
    s16 selection;
    s16 count;
} PanelState;

extern PanelState *g_panelState_0206f9a0;
extern u8 data_ov014_0206f81c[][7];
extern char data_ov014_0206f954[];

extern void func_ov002_0206203c(int selector);
extern void func_ov002_020620fc(int selector);
extern int DispatchContextCommand_02066c78(int command, int value, int extra, void *buffer);
extern int GetPackedField_02069690(void *info, int category, int entry);
extern void *func_ov002_020621c4(int index, int extra);
extern void func_ov002_02061e34(int a, int b, int x, int y, int c, int d, int e, int f, const void *text);
extern void *func_0202e060(void *dst, const char *fmt, ...);
extern void CopyRecordName_02069d5c(s32 category, s32 index, u16 *dst);

void DrawSelectedEntryInfo_0206ea4c(BOOL keepLayer)
{
    u16 text[0x20] = {0};
    u8 category;
    u8 entry;

    if (!keepLayer) {
        func_ov002_0206203c(-1);
    }
    func_ov002_020620fc(1);
    category = data_ov014_0206f81c[g_panelState_0206f9a0->group][g_panelState_0206f9a0->index];
    entry = g_panelState_0206f9a0->groupEntries[category][g_panelState_0206f9a0->selection];
    if (DispatchContextCommand_02066c78(0xe, 0, 0, 0) == 1) {
        if (entry == GetPackedField_02069690(0, category, entry)) {
            func_ov002_02061e34(1, 1, 0x30, 0x26, 2, 8, 0, 1, func_ov002_020621c4(0x71, 0));
        }
        if (g_panelState_0206f9a0->count != 0) {
            func_0202e060(text, data_ov014_0206f954, g_panelState_0206f9a0->selection + 1,
                          g_panelState_0206f9a0->count);
            func_ov002_02061e34(1, 1, 0x40, 0x6a, 2, 0xc, 1, 0, text);
        }
    }
    CopyRecordName_02069d5c(category, entry, g_panelState_0206f9a0->entryName);
    func_ov002_02061e34(1, 1, 0x80, 0xb3, 2, 0xc, 1, 0, g_panelState_0206f9a0->entryName);
}
