#include "nitro/types.h"

typedef struct OSThread {
    u8 pad_00[0x64];
    u32 state;
    u8 pad_68[0x78 - 0x68];
    struct OSThreadQueue *queue;
    u8 pad_7c[0x9c - 0x7c];
    u8 joinQueue[8];
} OSThread;

typedef struct {
    u8 pad_00[8];
    OSThread **currentThreadPtr;
} SchedulerGlobals_02056b50;

extern SchedulerGlobals_02056b50 data_02056b50;
extern void func_02002d70(void);
extern void func_020031b8(OSThread *thread);
extern OSThread *OSi_RemoveSpecifiedLinkFromQueue(struct OSThreadQueue *queue, OSThread *thread);
extern void func_02002640(OSThread *thread);
extern void OS_WakeupThread_02002af8(void *queue);
extern void func_02002da0(void);
extern void OS_RescheduleThread_02002bb4(void);
extern void func_02004cf0(void);

void DestroyCurrentThread_02002a38(void)
{
    OSThread *currentThread = *data_02056b50.currentThreadPtr;

    func_02002d70();
    func_020031b8(currentThread);
    if (currentThread->queue != 0) {
        OSi_RemoveSpecifiedLinkFromQueue(currentThread->queue, currentThread);
    }
    func_02002640(currentThread);
    currentThread->state = 2;
    OS_WakeupThread_02002af8(currentThread->joinQueue);
    func_02002da0();
    OS_RescheduleThread_02002bb4();
    func_02004cf0();
}
