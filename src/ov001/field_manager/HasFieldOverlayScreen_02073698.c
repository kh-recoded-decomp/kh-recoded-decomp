#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x42c];
    void *overlayScreen;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

BOOL HasFieldOverlayScreen_02073698(void)
{
    if (data_ov001_020a04a4.manager->overlayScreen != NULL) {
        return TRUE;
    }
    return FALSE;
}
