#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0x118];
} PanelState;

extern PanelState *data_ov002_0206c460;
extern int func_ov027_020ba2c8(void *state, int index);

int func_ov002_020621c4(int index) {
    return func_ov027_020ba2c8((u8 *)data_ov002_0206c460 + 0x118, index);
}
