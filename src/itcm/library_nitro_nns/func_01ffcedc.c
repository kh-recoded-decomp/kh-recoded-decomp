/* Queues a command and argument while busy, or flushes queued words and writes pair to GXFIFO.
 * The middleware operation is supported by this body; its caller-specific use and any higher-level game meaning are not established here. */
/* Recovered CC0 library C from Yokimitsuro/khdays-decomp, revision
 * ab832f38b943c15f461228968a89002e1a99c03e, libs/nitro/nns/calls/func_01ffa764.c.
 * Original routine: func_01ffa764. External references are
 * rebound to BK9E; subsystem identity is reviewed separately from matching. */
typedef unsigned long u32;

typedef struct NNSG3dGeCommandBuffer {
    u32 count;
    u32 words[0xc0];
} NNSG3dGeCommandBuffer;

extern void MIi_CpuSend32(const void *src, volatile void *dst, u32 size);

extern NNSG3dGeCommandBuffer *data_027e00a8;
extern volatile u32 data_027e00ac;

void QueueOrSendGeometryCommandPair_01ffcedc(u32 command, u32 argument)
{
    NNSG3dGeCommandBuffer *buffer = data_027e00a8;
    volatile u32 *busyFlag = &data_027e00ac;
    u32 count = buffer->count;

    if (*busyFlag != 0) {
        if (count + 2 <= 0xc0) {
            buffer->words[count] = command;
            buffer->words[count + 1] = argument;
            buffer->count += 2;
            return;
        }

        while (*busyFlag != 0) {
        }
    }

    if (count != 0) {
        MIi_CpuSend32(buffer->words, (volatile void *)0x04000400,
                      count << 2);
        buffer->count = 0;
    }

    *(volatile u32 *)0x04000400 = command;
    *(volatile u32 *)0x04000400 = argument;
}
