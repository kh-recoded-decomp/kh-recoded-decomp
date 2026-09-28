#include "nitro/types.h"

typedef void (*ResetCallback)(u32 arg);

typedef struct {
    ResetCallback callback;
    u32 arg;
} ResetCallbackSlot;

extern ResetCallbackSlot g_resetCallbackSlot_02056ee0;
extern void OSi_IdleThreadProc_02004d20(void);

void RunResetCallbackAndIdle_02004cf0(void)
{
    ResetCallback callback = g_resetCallbackSlot_02056ee0.callback;

    if (callback != NULL) {
        g_resetCallbackSlot_02056ee0.callback = NULL;
        callback(g_resetCallbackSlot_02056ee0.arg);
    }

    OSi_IdleThreadProc_02004d20();
}
