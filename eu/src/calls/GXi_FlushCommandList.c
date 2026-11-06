#include "nitro/types.h"

typedef struct NNSG3dGeBuffer {
    u32 idx;
    u32 data[1];
} NNSG3dGeBuffer;

extern void WaitForGeometryTransfer(int unused);
extern void MIi_CpuSend32(const void *src, volatile void *dest, u32 size);
extern NNSG3dGeBuffer *gGeometryCommandBuffer;
extern volatile int gGeometryTransferBusy;

void GXi_FlushCommandList(void) {
    int busy = gGeometryTransferBusy;
    if (busy != 0) {
        WaitForGeometryTransfer(busy);
    }
    if (gGeometryCommandBuffer != NULL && gGeometryCommandBuffer->idx != 0) {
        MIi_CpuSend32(gGeometryCommandBuffer->data, (volatile void *)0x04000400, gGeometryCommandBuffer->idx << 2);
        gGeometryCommandBuffer->idx = 0;
    }
}
