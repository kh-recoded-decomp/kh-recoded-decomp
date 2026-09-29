#include "nitro/types.h"

typedef struct OSThread OSThread;

struct OSThread {
    u8 context[0x64];
    u32 state;
    OSThread *next;
    u32 id;
    u32 priority;
    void *profiler;
    void *queue;
    OSThread *linkPrev;
    OSThread *linkNext;
    void *mutex;
    void *mutexQueueHead;
    void *mutexQueueTail;
    u32 stackTop;
    u32 stackBottom;
    u32 stackWarningOffset;
    OSThread *joinQueueHead;
    OSThread *joinQueueTail;
    void *specific[3];
    void *alarmForSleep;
    void *destructor;
    void *userParameter;
    int systemErrno;
};

typedef struct OSThreadInfo {
    u16 isNeedRescheduling;
    u16 irqDepth;
    OSThread *current;
    OSThread *list;
    void *switchCallback;
} OSThreadInfo;

typedef struct OSThreadSystem {
    u32 unused_00;
    u32 rescheduleCount;
    OSThread **currentThreadPtr;
    BOOL isThreadInitialized;
    u32 unused_10[2];
    int threadIdCount;
    OSThreadInfo threadInfo;
} OSThreadSystem;

extern OSThreadSystem data_02056b50;
extern OSThread data_02056b7c;
extern OSThread data_02056c3c;
extern u32 data_02056cfc[50];
extern unsigned char data_027e0000[];
extern void SDK_SYS_STACKSIZE_00000000(void);
extern void SDK_IRQ_STACKSIZE_00000800(void);

extern u32 SetSchedulerField28_02002d38(u32 value);
extern void OS_CreateThread_02002898(OSThread *thread, void (*func)(void *), void *arg, void *stack, u32 stackSize, u32 priority);
extern void OSi_IdleThreadProc_02002d60(void *arg);

#define OSi_SYS_STACKSIZE ((s32)SDK_SYS_STACKSIZE_00000000)
#define OSi_IRQ_STACKSIZE ((s32)SDK_IRQ_STACKSIZE_00000800)
#define OSi_LAUNCHER_STACK_LO_DEFAULT 0x027e0280
#define OSi_LAUNCHER_STACK_BOTTOM ((u32)data_027e0000 + 0x3f80 - OSi_IRQ_STACKSIZE)

void OS_InitThread_0200274c(void)
{
    void *stackLo;

    if (data_02056b50.isThreadInitialized) {
        return;
    }
    data_02056b50.isThreadInitialized = TRUE;

    data_02056b50.currentThreadPtr = &data_02056b50.threadInfo.current;
    data_02056c3c.priority = 16;
    data_02056c3c.id = 0;
    data_02056c3c.state = 1;
    data_02056c3c.next = NULL;
    data_02056c3c.profiler = NULL;

    data_02056b50.threadInfo.list = &data_02056c3c;
    data_02056b50.threadInfo.current = &data_02056c3c;

    stackLo = (OSi_SYS_STACKSIZE <= 0) ?
              (void *)((u32)OSi_LAUNCHER_STACK_LO_DEFAULT - OSi_SYS_STACKSIZE) :
              (void *)(OSi_LAUNCHER_STACK_BOTTOM - OSi_SYS_STACKSIZE);

    data_02056c3c.stackBottom = OSi_LAUNCHER_STACK_BOTTOM;
    data_02056c3c.stackTop = (u32)stackLo;
    data_02056c3c.stackWarningOffset = 0;

    *(u32 *)(data_02056c3c.stackBottom - sizeof(u32) * 2) = 0xFDDB597D;
    *(u32 *)data_02056c3c.stackTop = 0x7BF9DD5B;

    data_02056c3c.joinQueueHead = data_02056c3c.joinQueueTail = NULL;

    data_02056b50.threadInfo.isNeedRescheduling = FALSE;
    data_02056b50.threadInfo.irqDepth = 0;

    *(OSThreadInfo **)0x02ffffa0 = &data_02056b50.threadInfo;

    SetSchedulerField28_02002d38(0);

    OS_CreateThread_02002898(&data_02056b7c, OSi_IdleThreadProc_02002d60, NULL, data_02056cfc + 50, sizeof(data_02056cfc), 31);

    data_02056b7c.priority = 32;
    data_02056b7c.state = 1;
}
