#include "nitro/types.h"

typedef struct PanelState {
    u8 pad_00[0xb8];
    u32 cullDepth;
} PanelState;

extern PanelState *data_ov031_020bc800;

u32 func_ov031_020bc700(void)
{
    return data_ov031_020bc800->cullDepth;
}
