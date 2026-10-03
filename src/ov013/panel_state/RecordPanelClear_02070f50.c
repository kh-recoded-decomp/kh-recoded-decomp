#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x258];
    u8 slotPending[1];
} PanelState;

extern PanelState *g_panelState_02074ce0;
extern int DispatchContextCommand_02066c78(u32 command, int value, int extra, void *buffer);

void RecordPanelClear_02070f50(int index) {
    int stage;
    int rollover;

    stage = index + 1;
    rollover = stage % 10;
    if (rollover != 0) {
        DispatchContextCommand_02066c78(0x8000000f, 1, index - stage / 10, NULL);
    } else {
        DispatchContextCommand_02066c78(0x8000000b, 1, stage, NULL);
    }
    g_panelState_02074ce0->slotPending[index] = 0;
    if (DispatchContextCommand_02066c78(7, 0, 0, NULL) < index + 1) {
        int tier;
        DispatchContextCommand_02066c78(0x80000007, index + 1, 0, NULL);
        tier = (index + 1) / 10;
        if (tier > DispatchContextCommand_02066c78(6, 0, 0, NULL)) {
            DispatchContextCommand_02066c78(0x80000006, tier, 0, NULL);
        }
    }
    if (DispatchContextCommand_02066c78(5, 0, 0, NULL) != 0) {
        DispatchContextCommand_02066c78(0x80000005, 0, 0, NULL);
    }
    if (rollover != 0) {
        DispatchContextCommand_02066c78(0x80000010, 0, index - (index + 1) / 10, NULL);
    }
}
