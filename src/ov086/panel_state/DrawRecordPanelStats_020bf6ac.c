#include "nitro/types.h"

typedef struct {
    int values[8];
} InitialValueTable;

typedef struct {
    u8 pad0[0xc];
    u8 handler[0x128];
    int group;
    u8 pad138[0x3c];
    u8 tileTable[4];
} RecordPanel;

extern const InitialValueTable data_ov086_020c21ec;
extern int data_ov086_020c2148[];
extern int data_ov086_020c215c[];
extern u32 data_ov086_020c217c[];
extern void CallVirtualHandlerSlot1_02001574(void *context, int arg);
extern void SetScreenLayerDirty_020bc104(int layerId);
extern void MarkTileTableRowDirty_020b9e00(void *table, int id);
extern u32 ReadSessionPackedBits_02064574(int bitOffset, u32 bitCount);
extern BOOL func_ov001_020645c8(u32 flagId);
extern int func_ov086_020bf290(int group);
extern int func_ov086_020bf324(int group);
extern int func_ov086_020bf394(int group);
extern int func_ov086_020bf484(int group);
extern int SumUnlockedGroupEntryCounts_020bf5d8(int group);
extern int GetHighestSetFlagTier_020bf658(int group);
extern void func_ov086_020bee0c();

void DrawRecordPanelStats_020bf6ac(RecordPanel *panel)
{
    InitialValueTable table = data_ov086_020c21ec;
    int group;
    int first;
    int second;

    CallVirtualHandlerSlot1_02001574(panel->handler, 0);
    SetScreenLayerDirty_020bc104(0x18);
    MarkTileTableRowDirty_020b9e00(panel->tileTable, 0x19);
    group = panel->group;
    func_ov086_020bee0c(panel, 0, func_ov086_020bf290(group), table.values[group]);
    group = panel->group;
    if (group < 5) {
        func_ov086_020bee0c(panel, 1, ReadSessionPackedBits_02064574(data_ov086_020c2148[group], 2), 3);
    } else {
        func_ov086_020bee0c(panel, 6, group);
    }
    first = func_ov086_020bf324(panel->group);
    func_ov086_020bee0c(panel, 2, first, func_ov086_020bf394(panel->group));
    first = func_ov086_020bf484(panel->group);
    func_ov086_020bee0c(panel, 3, first, SumUnlockedGroupEntryCounts_020bf5d8(panel->group));
    func_ov086_020bee0c(panel, 4, GetHighestSetFlagTier_020bf658(panel->group));
    first = ReadSessionPackedBits_02064574(data_ov086_020c215c[panel->group], 7);
    second = func_ov001_020645c8(data_ov086_020c217c[panel->group]);
    func_ov086_020bee0c(panel, 5, first + 1, second);
}
