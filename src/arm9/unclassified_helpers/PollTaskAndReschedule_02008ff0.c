#include "nitro/types.h"

typedef int (*PollFunc)(u32 arg);

extern void SetFlagsAndWake_02004df8(u32 *flags, u32 mask);
extern void func_02004668(void *state, int period, int value, void *callback, void *task);
extern void SelfReschedule_02008ff0(u32 *task);

void PollTaskAndReschedule_02008ff0(u32 *task)
{
    PollFunc poll = *(PollFunc *)((u8 *)task + 0x34);
    u32 arg = *(u32 *)((u8 *)task + 0x38);

    if (poll(arg) != 0) {
        SetFlagsAndWake_02004df8(task, 1);
        return;
    }
    func_02004668((u8 *)task + 0xc, 0xc0, 0x107, SelfReschedule_02008ff0, task);
}
