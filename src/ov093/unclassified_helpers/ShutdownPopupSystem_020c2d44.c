#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    void *resourceFile;
} PopupWork;

extern PopupWork *g_popupWork_020c50e4;
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void ShutdownPopupSystem_020c2d44(void)
{
    if (g_popupWork_020c50e4->resourceFile != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(g_popupWork_020c50e4->resourceFile);
        g_popupWork_020c50e4->resourceFile = NULL;
    }
    g_popupWork_020c50e4 = NULL;
}
