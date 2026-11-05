#include "nitro/types.h"

extern u32 data_ov001_020a0480;
extern u32 QueueFieldFromSavedSceneIds();

void QueueSavedFieldAndClearFlag14(void) {
    QueueFieldFromSavedSceneIds();
    *(u32 *)(data_ov001_020a0480 + 0x214) = *(u32 *)(data_ov001_020a0480 + 0x214) & 0xffffbfff;
}
