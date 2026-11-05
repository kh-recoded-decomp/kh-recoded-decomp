#include "nitro/types.h"

extern u32 IsPanelMapUpdateAllowed(s32 panel);
extern void MarkMapMenuDirty(void);

extern u32 data_ov001_020a04e8;

void MarkPanelMapTransformDirty(void)
{
    u32 ready;

    ready = IsPanelMapUpdateAllowed(data_ov001_020a04e8);
    if (ready != 0) {
        MarkMapMenuDirty();
    }
}
