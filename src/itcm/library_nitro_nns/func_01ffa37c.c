/* Queues a command plus argument words while busy, otherwise flushes and writes to GXFIFO.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/func_01ff9f00.c.
 * Original routine: func_01ff9f00. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned long u32;

typedef struct NNSG3dGeBuffer {
    u32 idx;
    u32 data[192];
} NNSG3dGeBuffer;

extern NNSG3dGeBuffer *data_027e00a8;
extern volatile int data_027e00ac;

extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern void MIi_CpuSend32(const void *src, volatile void *dst, u32 size);

void QueueOrSendGeometryCommand_01ffa37c(u32 op, const u32 *args, u32 numWords)
{
    NNSG3dGeBuffer *buffer = data_027e00a8;
    int busyValue = data_027e00ac;
    u32 idx = buffer->idx;

    if (busyValue != 0) {
        if (idx + 1 + numWords <= 192) {
            buffer->data[idx++] = op;
            if (numWords > 0) {
                MIi_CpuCopyFast(args, &data_027e00a8->data[idx], numWords << 2);
                idx += numWords;
            }
            data_027e00a8->idx = idx;
            return;
        }
        while (data_027e00ac != 0) {
        }
    }

    if (idx != 0) {
        MIi_CpuSend32(&buffer->data[0], (volatile void *)0x04000400, idx << 2);
        data_027e00a8->idx = 0;
    }

    *(volatile u32 *)0x04000400 = op;
    MIi_CpuSend32(args, (volatile void *)0x04000400, numWords << 2);
}
