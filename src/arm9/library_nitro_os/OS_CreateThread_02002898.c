#include "nitro/types.h"

typedef void (*OSThreadFunc)(void *arg);

typedef struct OSThread {
    u8 pad_00[4];
    void *arg;
    u8 pad_08[0x34];
    void *exitHook;
    u8 pad_40[0x24];
    u32 state;
    struct OSThread *next;
    u32 id;
    u32 priority;
    void *profiler;
    void *queue;
    struct OSThread *linkPrev;
    struct OSThread *linkNext;
    void *mutex;
    void *mutexQueueHead;
    void *mutexQueueTail;
    u32 stackTop;
    u32 stackBottom;
    u32 stackWarningOffset;
    struct OSThread *joinQueueHead;
    struct OSThread *joinQueueTail;
    void *specific[3];
    void *alarmForSleep;
} OSThread;

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern u32 AllocateNextThreadId_0200249c(void);
extern void InsertThreadByPriority_020025e4(OSThread *thread);
extern void func_02002ddc(OSThread *thread, OSThreadFunc func, u32 stack);
extern void OS_SetThreadDestructor(OSThread *thread, void *destructor);
extern void func_01ff86fc(u32 value, void *destination, u32 size);
extern void ExitCurrentThread_02002988(void);

void OS_CreateThread_02002898(OSThread *thread, OSThreadFunc func, void *arg, void *stack, u32 stackSize, u32 priority)
{
    u32 interruptState = func_02004938();
    u32 id = AllocateNextThreadId_0200249c();

    thread->priority = priority;
    thread->id = id;
    thread->state = 0;
    thread->profiler = NULL;
    InsertThreadByPriority_020025e4(thread);

    thread->stackBottom = (u32)stack;
    thread->stackTop = (u32)stack - stackSize;
    thread->stackWarningOffset = 0;
    *(u32 *)(thread->stackBottom - sizeof(u32) * 2) = 0xFDDB597D;
    *(u32 *)thread->stackTop = 0x7BF9DD5B;
    thread->joinQueueHead = thread->joinQueueTail = NULL;

    func_02002ddc(thread, func, (u32)stack - sizeof(u32) * 2);
    thread->arg = arg;
    thread->exitHook = (void *)ExitCurrentThread_02002988;
    func_01ff86fc(0, (void *)((u32)stack - stackSize + sizeof(u32)), stackSize - sizeof(u32) * 3);

    thread->mutex = NULL;
    thread->mutexQueueHead = NULL;
    thread->mutexQueueTail = NULL;
    OS_SetThreadDestructor(thread, NULL);

    thread->queue = NULL;
    thread->linkPrev = thread->linkNext = NULL;
    func_01ff86fc(0, thread->specific, sizeof(thread->specific));

    thread->alarmForSleep = NULL;
    func_0200494c(interruptState);
}
