#include "nitro/types.h"

typedef struct OSThread {
    u8 pad_00[0x68];
    struct OSThread *next;
} OSThread;

typedef struct {
    u8 pad_00[0x24];
    OSThread *threadList;
} SchedulerGlobals_02056b50;

extern SchedulerGlobals_02056b50 data_02056b50;

void RemoveThreadFromList_02002640(OSThread *thread)
{
    OSThread *previous = NULL;
    OSThread *current = data_02056b50.threadList;

    while (current != 0 && current != thread) {
        previous = current;
        current = current->next;
    }
    if (previous == 0) {
        data_02056b50.threadList = thread->next;
    } else {
        previous->next = thread->next;
    }
}
