#include "nitro/types.h"

typedef struct NNSG3dGeBuffer {
    u32 idx;
    u32 data[1];
} NNSG3dGeBuffer;

extern void FSi_WaitForCardThread(int unused);
extern void MIi_CpuSend32(const void *src, volatile void *dest, u32 size);
extern NNSG3dGeBuffer *data_027e00a8;
extern volatile int data_027e00ac;

void GXi_FlushCommandList(void) {
    int busy = data_027e00ac;
    if (busy != 0) {
        FSi_WaitForCardThread(busy);
    }
    if (data_027e00a8 != NULL && data_027e00a8->idx != 0) {
        MIi_CpuSend32(data_027e00a8->data, (volatile void *)0x04000400, data_027e00a8->idx << 2);
        data_027e00a8->idx = 0;
    }
}
