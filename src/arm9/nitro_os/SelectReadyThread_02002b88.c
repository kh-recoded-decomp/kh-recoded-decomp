#include "nitro/types.h"

typedef struct OSThread {
    u8 pad_00[0x64];
    u32 state;
    struct OSThread *next;
} OSThread;

typedef struct {
    u8 pad_00[0x24];
    OSThread *list;
} ThreadInfo_02056b50;

extern ThreadInfo_02056b50 data_02056b50;

void *SelectReadyThread_02002b88(void)
{
    OSThread *thread = data_02056b50.list;
    while (thread != NULL && thread->state != 1) {
        thread = thread->next;
    }
    return thread;
}
