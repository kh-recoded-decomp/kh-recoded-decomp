#include "nitro/types.h"

typedef struct OSThreadQueue {
    void *head;
    void *tail;
} OSThreadQueue;

typedef struct {
    vu32 flag;
    OSThreadQueue queue;
} OSEvent;

typedef enum {
    OS_EVENTMODE_AND = 0,
    OS_EVENTMODE_OR = 1
} OSEventMode;

extern int OS_DisableInterrupts_02004938(void);
extern int OS_RestoreInterrupts_0200494c(int state);
extern void SleepCurrentThread_02002aa8(OSThreadQueue *queue);

u32 OS_WaitEventEx_02004d50(OSEvent *event, u32 pattern, OSEventMode mode, u32 clearBit)
{
    u32 result = 0;
    int enabled;

    enabled = OS_DisableInterrupts_02004938();

    switch (mode) {
    case OS_EVENTMODE_AND:
        while ((event->flag & pattern) != pattern) {
            SleepCurrentThread_02002aa8(&event->queue);
        }
        result = event->flag;
        break;
    case OS_EVENTMODE_OR:
        while (!(event->flag & pattern)) {
            SleepCurrentThread_02002aa8(&event->queue);
        }
        result = event->flag;
        break;
    }

    if (result) {
        event->flag &= ~clearBit;
    }

    (void)OS_RestoreInterrupts_0200494c(enabled);
    return result;
}
