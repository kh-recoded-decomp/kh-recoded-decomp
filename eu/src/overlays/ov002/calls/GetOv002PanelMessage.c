#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x118];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern int GetPackedFileEntry(void *state, int index);

int GetOv002PanelMessage(int index) {
    return GetPackedFileEntry((u8 *)data_ov002_0206c460 + 0x118, index);
}
