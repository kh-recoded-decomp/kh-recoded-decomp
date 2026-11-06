#include "libs/nitro/os/os_interrupt_state.h"

typedef unsigned long u32;
typedef u32 OSIntrMode;

typedef struct SNDCommand {
    struct SNDCommand *next;
    u32 id;
    u32 arguments[4];
} SNDCommand;

typedef struct SNDCommandState {
    SNDCommand *freeList;
    u32 finishedTag;
    SNDCommand *reserveList;
    SNDCommand *reserveListEnd;
    SNDCommand *freeListEnd;
    int waitingQueueRead;
    int waitingQueueWrite;
    int waitingListCount;
    u32 currentTag;
} SNDCommandState;

#define SND_COMMAND_BLOCK 1
#define SND_PXI_FIFO_MESSAGE_BUFSIZE 8

extern SNDCommandState gSoundCommandQueueState;
extern SNDCommand *gSoundSubmittedCommandListsStorage[SND_PXI_FIFO_MESSAGE_BUFSIZE + 1];
extern OSIntrMode OS_DisableInterrupts(void);

extern void OS_SpinWait(u32 cycles);
extern u32 SNDi_GetFinishedCommandTag(void);

const SNDCommand *SND_RecvCommandReply(u32 flags)
{
    OSIntrMode interruptState = OS_DisableInterrupts();
    SNDCommand *commandList;
    SNDCommand *commandListEnd;

    if (flags & SND_COMMAND_BLOCK) {
        while (gSoundCommandQueueState.finishedTag == SNDi_GetFinishedCommandTag()) {
            (void)OS_RestoreInterrupts(interruptState);
            OS_SpinWait(50);
            interruptState = OS_DisableInterrupts();
        }
    } else {
        if (gSoundCommandQueueState.finishedTag == SNDi_GetFinishedCommandTag()) {
            (void)OS_RestoreInterrupts(interruptState);
            return 0;
        }
    }

    commandList = gSoundSubmittedCommandListsStorage[gSoundCommandQueueState.waitingQueueRead];
    gSoundCommandQueueState.waitingQueueRead++;
    if (gSoundCommandQueueState.waitingQueueRead > SND_PXI_FIFO_MESSAGE_BUFSIZE) {
        gSoundCommandQueueState.waitingQueueRead = 0;
    }

    commandListEnd = commandList;
    while (commandListEnd->next) {
        commandListEnd = commandListEnd->next;
    }

    if (gSoundCommandQueueState.freeListEnd) {
        gSoundCommandQueueState.freeListEnd->next = commandList;
    } else {
        gSoundCommandQueueState.freeList = commandList;
    }
    gSoundCommandQueueState.freeListEnd = commandListEnd;

    gSoundCommandQueueState.waitingListCount--;
    gSoundCommandQueueState.finishedTag++;

    (void)OS_RestoreInterrupts(interruptState);
    return commandList;
}