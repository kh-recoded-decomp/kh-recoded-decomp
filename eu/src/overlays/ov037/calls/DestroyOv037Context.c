#include "nitro/types.h"

extern u8 *gContinueScreenContext;
extern char OVERLAY_27_ID[];
extern void func_ov027_020b7e1c(void *list);
extern void FreeAllocatedBuffers(void *buffers);
extern void DestroyFndObjectList(void *list);
extern void ReleaseModelAnimationResources(void *resource);
extern void ReleaseResourceAndDetach(void *resource);
extern void UnloadOverlayAfterGeometryTransfer(int target, int overlayId);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void DestroyOv037Context(void)
{
    if (gContinueScreenContext == NULL) {
        return;
    }
    func_ov027_020b7e1c(gContinueScreenContext + 0x8);
    FreeAllocatedBuffers(gContinueScreenContext + 0x54);
    DestroyFndObjectList(gContinueScreenContext + 0x1f4);
    ReleaseModelAnimationResources(gContinueScreenContext + 0x174);
    ReleaseResourceAndDetach(gContinueScreenContext + 0x70);
    UnloadOverlayAfterGeometryTransfer(0, (int)OVERLAY_27_ID);
    NNSi_FndFreeFromDefaultHeap(gContinueScreenContext);
    gContinueScreenContext = NULL;
}
