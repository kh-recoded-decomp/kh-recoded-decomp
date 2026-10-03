#include "nitro/types.h"

typedef struct PendingState {
    u8 pad_00[0x10];
    int pending;
    int index;
} PendingState;

extern PendingState data_ov021_020b5620;
extern int data_ov021_020b5624[];

void SetPendingFromTable_020a9598(int index)
{
    if (data_ov021_020b5620.pending == 0) {
        data_ov021_020b5620.pending = data_ov021_020b5624[index];
        data_ov021_020b5620.index = index;
    }
}
