#include "nitro/types.h"

typedef struct NNSG3dGeBuffer {
    u32 idx;
    u32 data[1];
} NNSG3dGeBuffer;

extern void FSi_WaitForCardThread_01ff8140(int unused);
extern void MI_CpuSend32_01ff8728(const void *src, volatile void *dest, u32 size);
extern NNSG3dGeBuffer *data_027e00a8;
extern volatile int data_027e00ac;

void NNS_G3dGeFlushBuffer_01ff80e4(void) {
    int busy = data_027e00ac;
    if (busy != 0) {
        FSi_WaitForCardThread_01ff8140(busy);
    }
    if (data_027e00a8 != NULL && data_027e00a8->idx != 0) {
        MI_CpuSend32_01ff8728(data_027e00a8->data, (volatile void *)0x04000400, data_027e00a8->idx << 2);
        data_027e00a8->idx = 0;
    }
}
