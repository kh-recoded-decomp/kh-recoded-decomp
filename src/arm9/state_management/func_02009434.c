#include "nitro/types.h"

typedef void (*CompletionCallback)(u32 arg);

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void OS_WakeupThread(void *queue);

void func_02009434(int request) {
    CompletionCallback callback;
    u32 arg;
    u32 state;

    callback = *(CompletionCallback *)(request + 0x4ec);
    arg = *(u32 *)(request + 0x4f0);
    state = func_02004938();
    *(u32 *)(request + 4) = *(u32 *)(request + 4) & 0xffffffb3;
    OS_WakeupThread((void *)(request + 0x4f4));
    func_0200494c(state);
    if (callback != 0) {
        callback(arg);
    }
}
