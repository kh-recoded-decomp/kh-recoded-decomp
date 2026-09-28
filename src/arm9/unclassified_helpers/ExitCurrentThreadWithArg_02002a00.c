#include "nitro/types.h"

typedef void (*ThreadDestructor)(void *arg);

typedef struct OSThread {
    u8 pad_00[0xb4];
    ThreadDestructor destructor;
} OSThread;

typedef struct {
    u8 pad_00[8];
    OSThread **currentThreadPtr;
} SchedulerGlobals_02056b50;

extern SchedulerGlobals_02056b50 data_02056b50;
extern void func_02004938(void);
extern void DestroyCurrentThread_02002a38(void);

void ExitCurrentThreadWithArg_02002a00(void *arg)
{
    OSThread *currentThread = *data_02056b50.currentThreadPtr;
    ThreadDestructor destructor = currentThread->destructor;

    if (destructor != 0) {
        currentThread->destructor = 0;
        destructor(arg);
        func_02004938();
    }
    DestroyCurrentThread_02002a38();
}
