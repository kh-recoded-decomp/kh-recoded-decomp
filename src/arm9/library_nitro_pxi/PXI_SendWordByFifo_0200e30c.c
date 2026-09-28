#include "nitro/types.h"

typedef struct PxiPacket {
    u32 nTag  : 5;
    u32 bErr  : 1;
    u32 nData : 26;
} PxiPacket;

typedef struct IpcFifoRegs {
    volatile u16 wCnt;
    u16          pad_02;
    volatile u32 dwSend;
} IpcFifoRegs;

extern int  OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

s32 PXI_SendWordByFifo_0200e30c(u32 nTag, u32 nData, u32 bErr)
{
    IpcFifoRegs *pFifo = (IpcFifoRegs *)0x04000184;
    PxiPacket packet;
    int state;

    packet.nTag = nTag;
    packet.bErr = bErr;
    packet.nData = nData;

    if (pFifo->wCnt & 0x4000) {
        pFifo->wCnt |= 0xc000;
        return -1;
    }
    state = OS_DisableInterrupts();
    if (pFifo->wCnt & 2) {
        OS_RestoreInterrupts(state);
        return -2;
    }
    pFifo->dwSend = *(u32 *)&packet;
    OS_RestoreInterrupts(state);
    return 0;
}
