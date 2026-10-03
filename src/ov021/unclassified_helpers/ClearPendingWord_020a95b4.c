#include "nitro/types.h"

typedef struct PendingState {
    u8 pad_00[0x10];
    int pending;
} PendingState;

extern PendingState data_ov021_020b5620;

void ClearPendingWord_020a95b4(void)
{
    if (data_ov021_020b5620.pending != 0) {
        data_ov021_020b5620.pending = 0;
    }
}
