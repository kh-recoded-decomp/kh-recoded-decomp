#include "nitro/types.h"

extern u8 *g_ov037Context_020bb764;
extern char OverlayId27_0000001b[];
extern void func_ov027_020b7dfc(void *list);
extern void FreeAllocatedBuffers_020b9a60(void *buffers);
extern void DestroyFndObjectList_020014f0(void *list);
extern void func_0202eaf4(void *resource);
extern void ReleaseResourceAndDetach_0202eee8(void *resource);
extern void func_02029f98(int target, int overlayId);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void DestroyOv037Context_020bb448(void)
{
    if (g_ov037Context_020bb764 == NULL) {
        return;
    }
    func_ov027_020b7dfc(g_ov037Context_020bb764 + 0x8);
    FreeAllocatedBuffers_020b9a60(g_ov037Context_020bb764 + 0x54);
    DestroyFndObjectList_020014f0(g_ov037Context_020bb764 + 0x1f4);
    func_0202eaf4(g_ov037Context_020bb764 + 0x174);
    ReleaseResourceAndDetach_0202eee8(g_ov037Context_020bb764 + 0x70);
    func_02029f98(0, (int)OverlayId27_0000001b);
    NNSi_FndFreeFromDefaultHeap_0202a1c4(g_ov037Context_020bb764);
    g_ov037Context_020bb764 = NULL;
}
