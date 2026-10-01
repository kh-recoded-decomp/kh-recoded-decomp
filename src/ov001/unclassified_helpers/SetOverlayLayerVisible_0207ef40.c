#include "nitro/types.h"

typedef struct LayerState {
    u8 pad_00[0x14];
    u8 flags;
} LayerState;

extern LayerState *data_ov001_020a04d8;
extern void func_ov001_02087030(BOOL visible);

void SetOverlayLayerVisible_0207ef40(BOOL visible)
{
    if (visible) {
        data_ov001_020a04d8->flags |= 1;
    } else {
        data_ov001_020a04d8->flags &= ~1;
    }
    func_ov001_02087030(visible);
}
