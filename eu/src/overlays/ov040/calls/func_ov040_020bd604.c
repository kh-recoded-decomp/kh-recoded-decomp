#include "nitro/types.h"

extern u32 gMovieContextState;
extern void StartIdleSceneObjects();
extern void SetFieldObjectInteractionsBlocked();

u32 func_ov040_020bd604(void)
{
    StartIdleSceneObjects();
    SetFieldObjectInteractionsBlocked(1);
    *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) | 0x20;
    return 0xf;
}
