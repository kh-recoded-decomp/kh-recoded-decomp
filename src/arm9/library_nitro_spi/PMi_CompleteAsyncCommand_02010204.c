#include "nitro/types.h"

typedef void (*PMCallback)(u32 result, void *arg);

typedef struct PMAsyncState {
    u8 pad_00[0x2c];
    u32 busy;
    PMCallback callback;
    void *arg;
    u32 reserved;
} PMAsyncState;

extern PMAsyncState data_020597c0;

void PMi_CompleteAsyncCommand_02010204(u32 result)
{
    PMCallback callback = data_020597c0.callback;
    void *arg = data_020597c0.arg;

    data_020597c0.busy = 0;

    if (callback != NULL) {
        data_020597c0.callback = NULL;
        callback(result, arg);
    }
}
