#ifndef FS_WAIT_INTERNAL_H
#define FS_WAIT_INTERNAL_H

#include "libs/nitro/os/os_interrupt_state.h"
#include "libs/nitro/fs/fs_internal.h"

static inline void FSi_WaitConditionOn(u32 *flags, u32 bits,
                                       OSThreadQueue *queue)
{
    OSIntrMode interruptState = OS_DisableInterrupts();

    while ((*flags & bits) == 0) {
        OS_SleepThread(queue);
    }
    (void)OS_RestoreInterrupts(interruptState);
}

static inline void FSi_WaitConditionOff(u32 *flags, u32 bits,
                                        OSThreadQueue *queue)
{
    OSIntrMode interruptState = OS_DisableInterrupts();

    while ((*flags & bits) != 0) {
        OS_SleepThread(queue);
    }
    (void)OS_RestoreInterrupts(interruptState);
}

#endif
