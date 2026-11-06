#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x118];
} PanelState;

extern PanelState *gOv002ProfilePanelWork;
extern int GetPackedFileEntry(void *state, int index);

int GetOv002PanelMessage(int index) {
    return GetPackedFileEntry((u8 *)gOv002ProfilePanelWork + 0x118, index);
}
