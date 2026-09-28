#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x84];
    void *waitingFor;
} OSThread;

typedef struct {
    u8 pad_00[4];
    OSThread *currentThread;
} ThreadInfo_02056b6c;

extern ThreadInfo_02056b6c data_02056b6c;
extern int func_02004938(void);
extern void func_0200494c(int state);
extern int func_02003200(void *mutex);
extern void SleepCurrentThread_02002aa8(void *queue);

void LockSyncObjectRetry_02003158(void *mutex)
{
    int state = func_02004938();
    OSThread *currentThread = data_02056b6c.currentThread;

top:
    if (func_02003200(mutex) != 0) {
        goto done;
    }
    currentThread->waitingFor = mutex;
    SleepCurrentThread_02002aa8(mutex);
    currentThread->waitingFor = NULL;
    goto top;

done:
    func_0200494c(state);
}
