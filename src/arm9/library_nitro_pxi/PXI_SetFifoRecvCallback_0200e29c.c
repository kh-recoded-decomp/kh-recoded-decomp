#include "nitro/types.h"

typedef struct PxiSystemWork {
    u8 pad_000[0x388];
    u32 callbackMask[2];
} PxiSystemWork;

extern int func_02004938(void);
extern void func_0200494c(int state);
extern void *data_02057b8c[32];

void PXI_SetFifoRecvCallback_0200e29c(u32 fifoTag, void *callback)
{
    PxiSystemWork *work = (PxiSystemWork *)0x02fffc00;
    int state = func_02004938();

    data_02057b8c[fifoTag] = callback;

    if (callback != 0) {
        work->callbackMask[0] |= (1 << fifoTag);
    } else {
        work->callbackMask[0] &= ~(1 << fifoTag);
    }

    func_0200494c(state);
}
