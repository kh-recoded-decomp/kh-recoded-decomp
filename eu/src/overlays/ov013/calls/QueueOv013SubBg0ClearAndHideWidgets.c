#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x98];
    u8 flags;
} PanelState;

extern PanelState *gOv013PanelGlobals;
extern int FindWidgetById(void *panel, int value);
extern void SetEntrySlotsVisible(void *panel, int value, int flag);

void QueueOv013SubBg0ClearAndHideWidgets(void) {
    gOv013PanelGlobals->flags |= 4;
    int result = FindWidgetById((u8 *)gOv013PanelGlobals + 0x6818, 9);
    SetEntrySlotsVisible((u8 *)gOv013PanelGlobals + 0x6818, result, 0);
    result = FindWidgetById((u8 *)gOv013PanelGlobals + 0x6818, 10);
    SetEntrySlotsVisible((u8 *)gOv013PanelGlobals + 0x6818, result, 0);
}
