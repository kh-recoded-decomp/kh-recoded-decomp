#include "nitro/types.h"

extern void StartSubsceneOverlayLoad(s32 panel, u32 count);
extern void UnloadSubsceneOverlayAndDestroyTask(s32 panel);
extern u32 StepSubScreenFade(void);
extern u32 IsFileLoadQueueEmpty(void);

void ReloadSubsceneOverlayAfterFade(s32 panel)
{
    u32 ready;

    ready = StepSubScreenFade();
    if ((ready != 0) && (ready = IsFileLoadQueueEmpty(), ready != 0)) {
        *(u32 *)(panel + 0xdc) = 0xffffffff;
        UnloadSubsceneOverlayAndDestroyTask(panel);
        StartSubsceneOverlayLoad(panel, *(u32 *)(panel + 0xd0));
        *(u32 *)(panel + 0x4c) = 0;
        *(u32 *)(panel + 0x30) = 2;
    }
}
