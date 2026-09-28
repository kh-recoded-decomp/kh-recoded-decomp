/* Adapted from the CC0 khdays-decomp source at revision ab832f38b943c15f461228968a89002e1a99c03e. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned long long u64;
typedef long long s64;
typedef int BOOL;
typedef int OSIntrMode;
typedef void *OSMessage;
typedef volatile unsigned short vu16;
typedef volatile unsigned int vu32;
typedef volatile unsigned char vu8;

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0
#define HW_MAIN_MEM 0x02000000


/* NitroSDK SND library (ARM9 side, snd_command.c): the command queue to the ARM7 sound driver. */
typedef int PXIFifoTag;
typedef struct SNDCommand {
    struct SNDCommand *next;      /* 0x00 */
    u32 id;                       /* 0x04 */
    u32 arg[4];                   /* 0x08 */
} SNDCommand;                     /* 0x18 */
typedef struct SNDSharedWork SNDSharedWork;
#define SND_COMMAND_NUM 256
#define SND_PXI_FIFO_MESSAGE_BUFSIZE 8
#define SND_COMMAND_NOBLOCK 0
#define SND_COMMAND_BLOCK 1
#define SND_COMMAND_SHARED_WORK 0x1d
#define PXI_FIFO_TAG_SOUND 7
#define PXI_PROC_ARM7 1

/* The target layout is visible in function 0200eec0 and neighboring command-queue code. */
typedef struct SNDCommandQueueState {
    SNDCommand *freeList;              /* 0x00 */
    u32 finishedTag;                   /* 0x04 */
    SNDCommand *reserveList;           /* 0x08 */
    SNDCommand *reserveListEnd;        /* 0x0c */
    SNDCommand *freeListEnd;           /* 0x10 */
    int waitingQueueRead;              /* 0x14 */
    int waitingQueueWrite;             /* 0x18 */
    int waitingQueueCount;             /* 0x1c */
    u32 currentTag;                    /* 0x20 */
    SNDCommand *waitingQueue[9];       /* 0x24 */
} SNDCommandQueueState;
extern SNDCommandQueueState data_02057c50;
#define sFreeList data_02057c50.freeList
#define sFinishedTag data_02057c50.finishedTag
#define sReserveList data_02057c50.reserveList
#define sReserveListEnd data_02057c50.reserveListEnd
#define sFreeListEnd data_02057c50.freeListEnd
#define sWaitingCommandListQueueRead data_02057c50.waitingQueueRead
#define sWaitingCommandListQueueWrite data_02057c50.waitingQueueWrite
#define sWaitingCommandListCount data_02057c50.waitingQueueCount
#define sCurrentTag data_02057c50.currentTag
#define sWaitingCommandListQueue data_02057c50.waitingQueue
extern SNDSharedWork data_020447a0;   /* sSharedWork (0x280 bytes in this SDK, unaligned) */
#define sSharedWork data_020447a0
extern SNDCommand data_02044a20[SND_COMMAND_NUM] __attribute__((aligned(32)));   /* sCommandArray */
#define sCommandArray data_02044a20
extern SNDSharedWork *data_02046280;   /* SNDi_SharedWork */
#define SNDi_SharedWork data_02046280

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void func_0200386c(u32 cycles);   /* OS_SpinWait */
#define OS_SpinWait func_0200386c
extern void PXI_SetFifoRecvCallback(int fifotag, void (*callback)(PXIFifoTag, u32, BOOL));
extern BOOL PXI_IsCallbackReady(int fifotag, int proc);
extern void PxiFifoCallback(PXIFifoTag tag, u32 data, BOOL err);
extern BOOL IsCommandAvailable(void);
extern void InitPXI(void);
extern void SNDi_InitSharedWork(SNDSharedWork *work);
extern u32 SNDi_GetFinishedCommandTag(void);
extern SNDCommand *SND_AllocCommand(u32 flags);
extern void func_02008788(SNDCommand *command);   /* SND_PushCommand */
#define SND_PushCommand func_02008788
extern BOOL func_020087c0(u32 flags);              /* SND_FlushCommand */
#define SND_FlushCommand func_020087c0

/* func_0200eec0 -- NitroSDK snd_command.c: SND_RecvCommandReply. */
const SNDCommand * func_0200eec0 (u32 flags)
{
    OSIntrMode bak_psr = OS_DisableInterrupts();
    SNDCommand * commandList;
    SNDCommand * commandListEnd;

    if (flags & SND_COMMAND_BLOCK) {
        while (sFinishedTag == SNDi_GetFinishedCommandTag()) {
            (void)OS_RestoreInterrupts(bak_psr);
            OS_SpinWait(50);
            bak_psr = OS_DisableInterrupts();
        }
    } else {
        if (sFinishedTag == SNDi_GetFinishedCommandTag()) {
            (void)OS_RestoreInterrupts(bak_psr);
            return NULL;
        }
    }

    commandList = sWaitingCommandListQueue[sWaitingCommandListQueueRead];
    sWaitingCommandListQueueRead++;
    if (sWaitingCommandListQueueRead > SND_PXI_FIFO_MESSAGE_BUFSIZE)
        sWaitingCommandListQueueRead = 0;

    commandListEnd = commandList;
    while (commandListEnd->next != NULL) {
        commandListEnd = commandListEnd->next;
    }

    if (sFreeListEnd != NULL) {
        sFreeListEnd->next = commandList;
    } else {
        sFreeList = commandList;
    }

    sFreeListEnd = commandListEnd;

    sWaitingCommandListCount--;
    sFinishedTag++;

    (void)OS_RestoreInterrupts(bak_psr);
    return commandList;
}
