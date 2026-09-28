#include "nitro/types.h"

extern u8 data_ov035_020bc4b8[8];
extern u8 data_ov035_020bc4c0[8];
extern int GFXi_EnqueueCommand_02014090(int type, int destOffset, void *source, int size);

void QueueColorUpload_020bb7d8(BOOL useHighColors) {
    u8 *colors = data_ov035_020bc4c0;

    if (!useHighColors) {
        colors = data_ov035_020bc4b8;
    }
    GFXi_EnqueueCommand_02014090(0xf, 0x186, colors, 8);
}
