#include "nitro/types.h"

extern int FindWidgetById(int panel, int value);
extern void SetFocusedWidget(int panel, int value);
extern void ResolveWidgetPositionComponents(int panel, int value, void *buffer, int flag);
extern void SetWidgetPosition(int panel, int value, void *buffer, int flag);
extern int data_ov013_02074ce0;

/* Positions cursor widget 0 at x=8 (fx32) and the selected list row. */
void PositionOv013CursorWidget(void) {
    u32 buffer[2];
    int result = FindWidgetById(data_ov013_02074ce0 + 0x6818, *(s8 *)(data_ov013_02074ce0 + 0x2ee) + 0x14);
    SetFocusedWidget(data_ov013_02074ce0 + 0x6818, result);
    ResolveWidgetPositionComponents(data_ov013_02074ce0 + 0x6818, result, buffer, 0);
    buffer[1] = *(int *)(data_ov013_02074ce0 + 0xa8) + *(int *)(data_ov013_02074ce0 + 0x2fc) * 0x1000;
    buffer[0] = 0x8000;
    result = FindWidgetById(data_ov013_02074ce0 + 0x6818, 0);
    SetWidgetPosition(data_ov013_02074ce0 + 0x6818, result, buffer, 0);
}
