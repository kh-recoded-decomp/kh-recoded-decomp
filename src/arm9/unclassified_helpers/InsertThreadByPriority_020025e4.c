#include "nitro/types.h"

typedef struct OSThread {
    u8 pad_00[0x68];
    struct OSThread *next;
    u8 pad_6c[4];
    u32 priority;
} OSThread;

typedef struct {
    u8 pad_00[0x24];
    OSThread *threadList;
} SchedulerGlobals_02056b50;

extern SchedulerGlobals_02056b50 data_02056b50;

void InsertThreadByPriority_020025e4(OSThread *thread)
{
    OSThread *current = data_02056b50.threadList;
    OSThread *previous = 0;

    while (current != 0 && current->priority < thread->priority) {
        previous = current;
        current = current->next;
    }

    if (previous == 0) {
        thread->next = data_02056b50.threadList;
        data_02056b50.threadList = thread;
    } else {
        thread->next = previous->next;
        previous->next = thread;
    }
}
