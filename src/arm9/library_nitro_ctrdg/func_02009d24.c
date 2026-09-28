#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    void (*onComplete)(u32 arg);
    u32 completeArg;
    u32 readPos;
    u32 writePos;
    s32 remaining;
} StreamRequest;

typedef struct {
    u8 pad_00[8];
    StreamRequest *request;
} Registry;

typedef struct {
    u8 pad_00[8];
    u32 arg;
    void *listener;
} NotifyBlock;

typedef void (*NotifyFunc)(u32 arg);

extern Registry data_02057620;
extern NotifyBlock data_020574e0;
extern void func_02009b0c(u32 offset);
extern unsigned OS_DisableIrqMask(unsigned mask);
extern unsigned OS_ResetRequestIrqMask(unsigned mask);
extern void func_02009b38(void);
extern void func_0200a0fc(void);

void func_02009d24(void) {
    StreamRequest *request = data_02057620.request;
    NotifyFunc notify;

    if (request == 0) {
        return;
    }

    request->readPos += 0x200;
    request->writePos += 0x200;
    request->remaining -= 0x200;

    if (request->remaining != 0) {
        func_02009b0c(request->readPos);
        return;
    }

    notify = *(NotifyFunc *)((u8 *)data_020574e0.listener + 4);
    notify(data_020574e0.arg);

    OS_DisableIrqMask(0x80000);
    OS_ResetRequestIrqMask(0x80000);
    data_02057620.request = 0;
    func_02009b38();
    func_0200a0fc();

    if (request->onComplete != 0) {
        request->onComplete(request->completeArg);
    }
}
