#include "nitro/types.h"

extern u32 IsPanelMapUpdateAllowed(s32 panel);
extern void MarkMapMenuDirty(void);

extern u32 gSubscenePanelWork;

void MarkPanelMapTransformDirty(void)
{
    u32 ready;

    ready = IsPanelMapUpdateAllowed(gSubscenePanelWork);
    if (ready != 0) {
        MarkMapMenuDirty();
    }
}
