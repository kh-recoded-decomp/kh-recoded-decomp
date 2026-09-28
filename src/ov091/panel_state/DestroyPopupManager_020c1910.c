#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x1c];
    void *fileData;
} PopupManager;

extern PopupManager *g_popupManager_020c373c;
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);

void DestroyPopupManager_020c1910(void)
{
    if (g_popupManager_020c373c->fileData != NULL) {
        NNSi_FndFreeFromDefaultHeap_0202a1c4(g_popupManager_020c373c->fileData);
        g_popupManager_020c373c->fileData = NULL;
    }
    g_popupManager_020c373c = NULL;
}
