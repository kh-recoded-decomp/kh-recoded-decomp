#include "nitro/types.h"

extern u32 func_02004938(void);
extern void func_0200494c(u32 state);
extern void OS_WakeupThread(void *queue);

void SetFlagsAndWake_02004df8(u32 *flags, u32 mask) {
    u32 state;

    state = func_02004938();
    if (mask != 0) {
        *flags = *flags | mask;
        OS_WakeupThread(flags + 1);
    }
    func_0200494c(state);
}
