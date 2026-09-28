/* Adapted from CC0 khdays-decomp, revision ab832f38b943c15f461228968a89002e1a99c03e. */
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

typedef struct SNDCommandQueueState {
    SNDCommand *freeList; u32 finishedTag; SNDCommand *reserveList; SNDCommand *reserveListEnd;
    SNDCommand *freeListEnd; int waitingQueueRead; int waitingQueueWrite; int waitingQueueCount;
    u32 currentTag; SNDCommand *waitingQueue[9];
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
extern SNDSharedWork data_02057ca0;
#define sSharedWork data_02057ca0
extern SNDCommand data_02057f20[SND_COMMAND_NUM] __attribute__((aligned(32)));
#define sCommandArray data_02057f20
extern SNDSharedWork *data_02059780;
#define SNDi_SharedWork data_02059780

extern OSIntrMode OS_DisableInterrupts(void);
extern OSIntrMode OS_RestoreInterrupts(OSIntrMode state);
extern void func_0200386c(u32 cycles);   /* OS_SpinWait */
#define OS_SpinWait func_0200386c
extern void PXI_SetFifoRecvCallback(int fifotag, void (*callback)(PXIFifoTag, u32, BOOL));
extern BOOL PXI_IsCallbackReady(int fifotag, int proc);
extern void PxiFifoCallback(PXIFifoTag tag, u32 data, BOOL err);
extern BOOL IsCommandAvailable(void);
extern void func_0200f3bc(void);
extern void func_0200f62c(SNDSharedWork *work);
extern u32 SNDi_GetFinishedCommandTag(void);
extern SNDCommand *func_0200efc0(u32 flags);
extern void func_0200f048(SNDCommand *command);   /* SND_PushCommand */
#define SND_PushCommand func_0200f048
extern BOOL func_0200f080(u32 flags);              /* SND_FlushCommand */
#define SND_FlushCommand func_0200f080

/* func_0200edf0 -- NitroSDK snd_command.c: SND_CommandInit. */
void func_0200edf0 (void)
{
    SNDCommand * command;
    int i;


    func_0200f3bc();


    sFreeList = &sCommandArray[0];
    for (i = 0; i < SND_COMMAND_NUM - 1; i++) {
        sCommandArray[i].next = &sCommandArray[i + 1];
    }
    sCommandArray[SND_COMMAND_NUM - 1].next = NULL;
    sFreeListEnd = &sCommandArray[SND_COMMAND_NUM - 1];

    sReserveList = NULL;
    sReserveListEnd = NULL;

    sWaitingCommandListCount = 0;

    sWaitingCommandListQueueRead = 0;
    sWaitingCommandListQueueWrite = 0;

    sCurrentTag = 1;
    sFinishedTag = 0;

    SNDi_SharedWork = &sSharedWork;
    func_0200f62c(SNDi_SharedWork);

    command = func_0200efc0(SND_COMMAND_BLOCK);
    if (command != NULL) {
        command->id = SND_COMMAND_SHARED_WORK;
        command->arg[0] = (u32)SNDi_SharedWork;

        SND_PushCommand(command);
        (void)SND_FlushCommand(SND_COMMAND_BLOCK);
    }

}
