#include "nitro/types.h"

extern void ReleaseResourceAndDetach(u8 *object);
extern void NNSi_FndFreeFromDefaultHeap(int allocationAddress);
extern s32 GetFieldSessionState(void);
extern void UnlinkPendingNode(int object);

void ReleaseKind6ObjectAttachment(int object)
{
    if (*(int *)(object + 0x48) != 0) {
        ReleaseResourceAndDetach((u8 *)*(int *)(object + 0x48));
        NNSi_FndFreeFromDefaultHeap(*(int *)(object + 0x48));
        *(int *)(object + 0x48) = 0;
    }
    if (GetFieldSessionState() == 7) {
        UnlinkPendingNode(object + 0xa8);
    }
}
