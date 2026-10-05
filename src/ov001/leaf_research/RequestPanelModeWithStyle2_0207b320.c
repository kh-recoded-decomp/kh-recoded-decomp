#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x108];
    u32 sessionFlags;
} PanelScene;

extern PanelScene *data_ov001_020a04c8;
extern BOOL RequestPanelModeChange_0207b27c(int mode);

BOOL RequestPanelModeWithStyle2_0207b320(int mode)
{
    data_ov001_020a04c8->sessionFlags = 2;
    return RequestPanelModeChange_0207b27c(mode);
}
