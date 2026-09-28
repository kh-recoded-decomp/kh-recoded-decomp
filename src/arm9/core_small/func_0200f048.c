/* CC0 Yokimitsuro/khdays-decomp revision ab832f38b943c15f461228968a89002e1a99c03e. */


extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int state);

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

void func_0200f048(SNDCommand *command) {
    SNDCommand *tail;
    int state;

    state = OS_DisableInterrupts();
    tail = data_02057c50.reservedTail;
    
    if (tail == 0) {
        data_02057c50.reservedHead = command;
        data_02057c50.reservedTail = command;
    } else {
        tail->next = command;
        data_02057c50.reservedTail = command;
    }
    command->next = 0;
    OS_RestoreInterrupts(state);
}
