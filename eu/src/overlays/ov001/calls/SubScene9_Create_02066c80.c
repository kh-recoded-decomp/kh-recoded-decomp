/* Preserve the original wrapper's CodeWarrior integer types. */
#include "../include/nitro/types.h"

#include "nitro/types.h"

/* The task runner consumes native 32-bit callback words; zero retains its current state. */
extern u32 FinishFadeTween(void);

extern void *GetRunningTaskWork(void);
extern void InitTween(void *state);
extern u32 gSubScene9Work;

u32 SubScene9_Create_02066c80(void)
{
    u8 *heap;

    heap = (u8 *)GetRunningTaskWork();
    gSubScene9Work = (u32)heap;
    *heap = 0;
    InitTween(heap + 8);
    return (u32)FinishFadeTween;
}
