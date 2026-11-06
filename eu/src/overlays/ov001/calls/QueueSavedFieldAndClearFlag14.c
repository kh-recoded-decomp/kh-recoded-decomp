#include "nitro/types.h"

extern u32 gFieldSessionWork;
extern u32 QueueFieldFromSavedSceneIds();

void QueueSavedFieldAndClearFlag14(void) {
    QueueFieldFromSavedSceneIds();
    *(u32 *)(gFieldSessionWork + 0x214) = *(u32 *)(gFieldSessionWork + 0x214) & 0xffffbfff;
}
