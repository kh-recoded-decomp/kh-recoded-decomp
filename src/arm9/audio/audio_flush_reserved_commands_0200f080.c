/* Submits the reserved sound command list to the ARM7, including interrupt-protected queue handling, cache flush, bounded in-flight blocks, and optional command processing.
 * Evidence: NitroSDK sound command manager layout, PXI send/reply calls, and queue state transitions in the source; Nintendo DS NitroSDK pattern.
 * Uncertainty: Queue fields and protocol behavior are strongly supported; exact local game integration is middleware.
 * Source: src/calls/func_020087c0.c from khdays-decomp, CC0, commit ab832f38b943c15f461228968a89002e1a99c03e. */


typedef struct SNDCommand {
    struct SNDCommand *next;
    unsigned int id;
    unsigned int arg[4];
} SNDCommand;

typedef struct SNDCommandMgr {
    SNDCommand *freeHead;
    unsigned int processedTag;
    SNDCommand *reservedHead;
    SNDCommand *reservedTail;
    SNDCommand *freeTail;
    unsigned int unk14;
    int sentRingIndex;
    int sentBlockCount;
    unsigned int nextTag;
} SNDCommandMgr;

extern SNDCommandMgr data_02057c50;
extern SNDCommand *data_02057c74[8];
extern SNDCommand data_02057f20[0x100];

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int interruptState);
extern void DC_FlushRange(void *address, unsigned int size);
extern SNDCommand *func_0200eec0(int block);
extern int func_0200e30c(int channel, unsigned int data, int err);
extern void RequestCommandProc(void);

int audio_flush_reserved_commands_0200f080(unsigned int submitFlags) {
    int interruptState = OS_DisableInterrupts();

    if (data_02057c50.reservedHead == 0) {
        OS_RestoreInterrupts(interruptState);
        return 1;
    }

    if (data_02057c50.sentBlockCount >= 8) {
        if ((submitFlags & 1) == 0) {
            OS_RestoreInterrupts(interruptState);
            return 0;
        }
        do {
            func_0200eec0(1);
        } while (data_02057c50.sentBlockCount >= 8);
        if (data_02057c50.reservedHead == 0) {
            OS_RestoreInterrupts(interruptState);
            return 1;
        }
    }

    DC_FlushRange(data_02057f20, sizeof(data_02057f20));

    if (func_0200e30c(7, (unsigned int)data_02057c50.reservedHead, 0) < 0) {
        if ((submitFlags & 1) == 0) {
            OS_RestoreInterrupts(interruptState);
            return 0;
        }
        while (data_02057c50.sentBlockCount >= 8 ||
               func_0200e30c(7, (unsigned int)data_02057c50.reservedHead, 0) < 0) {
            OS_RestoreInterrupts(interruptState);
            func_0200eec0(0);
            interruptState = OS_DisableInterrupts();
            DC_FlushRange(data_02057f20, sizeof(data_02057f20));
            if (data_02057c50.reservedHead == 0) {
                OS_RestoreInterrupts(interruptState);
                return 1;
            }
        }
    }

    data_02057c74[data_02057c50.sentRingIndex] = data_02057c50.reservedHead;
    data_02057c50.sentRingIndex++;
    if (data_02057c50.sentRingIndex > 8) {
        data_02057c50.sentRingIndex = 0;
    }
    data_02057c50.reservedHead = 0;
    data_02057c50.reservedTail = 0;
    data_02057c50.sentBlockCount++;
    data_02057c50.nextTag++;
    OS_RestoreInterrupts(interruptState);

    if ((submitFlags & 2) != 0) {
        RequestCommandProc();
    }
    return 1;
}
