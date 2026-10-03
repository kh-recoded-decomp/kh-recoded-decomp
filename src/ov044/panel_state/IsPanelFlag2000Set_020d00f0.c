#include "nitro/types.h"

typedef struct {
    u8 _0[0x38];
    u32 flags;
} PanelState;

extern PanelState *data_ov044_020d0ea0;

u32 IsPanelFlag2000Set_020d00f0(void) {
    PanelState *panel = data_ov044_020d0ea0;
    if (panel != NULL) {
        return panel->flags & 0x2000;
    }
    return 0;
}
