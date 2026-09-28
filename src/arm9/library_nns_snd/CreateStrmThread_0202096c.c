#include "nitro/types.h"

typedef struct ThreadQueue {
    void *head;
    void *tail;
} ThreadQueue;

typedef struct StrmThreadState {
    u8 thread[0xc0];
    u8 stack[0x1000];
    ThreadQueue threadQ;
    u8 mutex[0x18];
    u8 commandList[0xc];
} StrmThreadState;

extern void func_02002898(void *thread, void (*entry)(StrmThreadState *), void *arg, void *stack, u32 stackSize, u32 priority);
extern void StrmThread_02021820(StrmThreadState *thread);
extern void func_0201288c(void *list, u32 linkOffset);
extern void InitSyncObject_02003134(void *mutex);
extern void OS_WakeupThreadDirect_02002b60(void *thread);

void CreateStrmThread_0202096c(StrmThreadState *thread, u32 priority)
{
    func_02002898(thread->thread, StrmThread_02021820, thread, thread->stack + 0x1000, 0x1000, priority);
    func_0201288c(thread->commandList, 0);
    InitSyncObject_02003134(thread->mutex);
    thread->threadQ.head = thread->threadQ.tail = NULL;
    OS_WakeupThreadDirect_02002b60(thread->thread);
}
