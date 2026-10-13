#include "src/overlays/ov086/RecordPageMenu.h"

typedef struct {
    RecordPageMenu menu;
    u8 reserved140[0x34];
    u8 flagTracker[0x1c];
} Ov086Menu;

extern void CallVirtualHandlerSlot1(void *context, int arg);
extern void SetScreenLayerDirty(int elementId);
extern void MarkTileTableRowDirty(u8 *tracker, int id);

void func_ov086_020bfba0(Ov086Menu *menu)
{
    CallVirtualHandlerSlot1(menu->menu.textLayer, 0);
    SetScreenLayerDirty(0x18);
    MarkTileTableRowDirty(menu->flagTracker, 0x19);
    DrawRecordStatisticsRow(&menu->menu, 0);
    DrawRecordStatisticsRow(&menu->menu, 1);
    DrawRecordStatisticsRow(&menu->menu, 2);
    DrawRecordStatisticsRow(&menu->menu, 3);
}
