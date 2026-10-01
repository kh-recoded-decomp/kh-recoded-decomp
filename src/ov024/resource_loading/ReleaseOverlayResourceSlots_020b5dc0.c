#include "nitro/types.h"

extern void *data_ov024_020b752c[6];
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *memory);

void ReleaseOverlayResourceSlots_020b5dc0(void)
{
    int slotIndex = 0;
    do {
        if (data_ov024_020b752c[slotIndex] != NULL) {
            NNSi_FndFreeFromDefaultHeap_0202a1c4(data_ov024_020b752c[slotIndex]);
            data_ov024_020b752c[slotIndex] = NULL;
        }
        slotIndex++;
    } while (slotIndex < 6);
}
