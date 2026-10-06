#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x98];
    u8 flags;
} PanelState;

extern PanelState *data_ov013_02074ce0;
extern int FindWidgetById(void *panel, int value);
extern void SetEntrySlotsVisible(void *panel, int value, int flag);

void func_ov013_02070aa0(void) {
    data_ov013_02074ce0->flags |= 4;
    int result = FindWidgetById((u8 *)data_ov013_02074ce0 + 0x6818, 9);
    SetEntrySlotsVisible((u8 *)data_ov013_02074ce0 + 0x6818, result, 0);
    result = FindWidgetById((u8 *)data_ov013_02074ce0 + 0x6818, 10);
    SetEntrySlotsVisible((u8 *)data_ov013_02074ce0 + 0x6818, result, 0);
}
