#include "nitro/types.h"

typedef struct OSThread {
    u8 pad_00[0x64];
    u32 state;
    u8 pad_68[0x78 - 0x68];
    struct OSThreadQueue *queue;
} OSThread;

typedef struct OSThreadQueue {
    OSThread *head;
    OSThread *tail;
} OSThreadQueue;

typedef struct {
    u8 pad_00[8];
    OSThread **currentThreadPtr;
} SchedulerGlobals_02056b50;

extern SchedulerGlobals_02056b50 data_02056b50;
extern u32 func_02004938(void);
extern void OSi_InsertLinkToQueue(OSThreadQueue *queue, OSThread *thread);
extern void func_02002688(void);
extern void func_0200494c(u32 state);

void SleepCurrentThread_02002aa8(OSThreadQueue *queue)
{
    u32 savedState = func_02004938();
    OSThread *currentThread = *data_02056b50.currentThreadPtr;

    if (queue != 0) {
        currentThread->queue = queue;
        OSi_InsertLinkToQueue(queue, currentThread);
    }
    currentThread->state = 0;
    func_02002688();
    func_0200494c(savedState);
}
