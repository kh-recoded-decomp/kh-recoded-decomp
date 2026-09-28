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
extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void PMi_SendPxiData_0201060c(int command);

/* locks and streams PXI command words */
u32 PMi_SendPxiCommandArray_02010300(u32 *words, int count, u32 reserved, PMCallback callback, void *arg)
{
    u32 state = func_02004938();

    if (data_020597c0.busy != 0) {
        func_0200494c(state);
        return 1;
    }

    data_020597c0.busy = 1;
    data_020597c0.reserved = reserved;
    data_020597c0.callback = callback;
    data_020597c0.arg = arg;

    for (int i = 0; i < count; i++) {
        PMi_SendPxiData_0201060c(words[i]);
    }

    func_0200494c(state);
    return 0;
}
