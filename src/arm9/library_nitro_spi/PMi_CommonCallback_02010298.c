#include "nitro/types.h"

typedef void (*PMCallback)(u32 result, void *arg);

typedef struct PMState {
    u16 initialized;
    u16 pad_02;
    u32 lastVBlankCount;
    u32 startVBlankCount;
    vu32 sleepEndFlag;
    u8 pad_10[0x1c];
    u32 busy;
    PMCallback callback;
    void *callbackArg;
    u16 *work;
} PMState;

extern PMState data_020597c0;

extern void PMi_CompleteAsyncCommand_02010204(u32 result);

void PMi_CommonCallback_02010298(u32 tag, u32 data, BOOL err)
{
    u16 command = (u16)((data & 0x7f00) >> 8);
    u16 pxiResult = (u16)(data & 0xff);

    if (err) {
        switch (command) {
        case 0x61:
        case 0x62:
            pxiResult = 1;
            break;
        default:
            pxiResult = 2;
            break;
        }
        PMi_CompleteAsyncCommand_02010204(pxiResult);
        return;
    }

    switch (command) {
    case 0x61:
        if (data_020597c0.work != NULL) {
            *data_020597c0.work = pxiResult;
        }
        pxiResult = 0;
        break;
    case 0x60:
        pxiResult = 0;
        break;
    case 0x62:
        break;
    case 0x63:
        data_020597c0.sleepEndFlag = TRUE;
        break;
    }

    PMi_CompleteAsyncCommand_02010204(pxiResult);
}
