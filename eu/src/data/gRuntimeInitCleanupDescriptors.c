#include "nitro/types.h"

extern void RunGlobalConstructors(void);
extern void StackAlloc_FreeIfSetB_020253f8(void);

void *const gRuntimeInitCleanupDescriptors[6] = {
    (void *)RunGlobalConstructors,
    (void *)0x00000031,
    (void *)0x00100100,
    (void *)StackAlloc_FreeIfSetB_020253f8,
    (void *)0x00000015,
    (void *)0x00100000,
};
