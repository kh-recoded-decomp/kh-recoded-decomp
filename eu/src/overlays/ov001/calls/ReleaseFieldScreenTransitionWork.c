#include "nitro/types.h"

extern int FreeBufferAndClearStatus(int obj);
extern int ZeroHalfThenFree(void *arg0);

extern u32 gFieldScreenTransitionWork;

void ReleaseFieldScreenTransitionWork(void)
{
    FreeBufferAndClearStatus(gFieldScreenTransitionWork + 0x30);
    ZeroHalfThenFree(*(void **)(gFieldScreenTransitionWork + 0x60));
    gFieldScreenTransitionWork = 0;
}
