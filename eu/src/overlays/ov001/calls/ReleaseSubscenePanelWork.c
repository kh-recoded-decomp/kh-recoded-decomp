#include "nitro/types.h"

extern void UnloadSubsceneOverlayAndDestroyTask(s32 panel);
extern void FreeBufferArray(s32 panel);
extern void ReleaseSubscenePanelBuffers(s32 panel);
extern void NNSi_FndFreeFromDefaultHeap();
extern void SetDisplaySetting(u32 flag);

extern u32 gSubscenePanelWork;

void ReleaseSubscenePanelWork(void)
{
    s32 panel;

    panel = gSubscenePanelWork;
    UnloadSubsceneOverlayAndDestroyTask(gSubscenePanelWork);
    FreeBufferArray(panel);
    ReleaseSubscenePanelBuffers(panel);
    if (*(u32 *)(panel + 4) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(panel + 4) = 0;
    }
    if (*(u32 *)(panel + 8) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(panel + 8) = 0;
    }
    if (*(u32 *)(panel + 0xc) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(panel + 0xc) = 0;
    }
    if (*(u32 *)(panel + 0x10) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(panel + 0x10) = 0;
    }
    if (*(u32 *)(panel + 0x18) != 0) {
        NNSi_FndFreeFromDefaultHeap();
        *(u32 *)(panel + 0x18) = 0;
    }
    SetDisplaySetting(0);
    gSubscenePanelWork = 0;
}
