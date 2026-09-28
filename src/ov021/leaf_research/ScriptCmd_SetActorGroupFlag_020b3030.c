#include "nitro/types.h"

extern u32 func_ov001_020969e0();
extern u32 func_ov021_020b0250();
extern u32 func_ov021_020b0374();

/* Leaf script command: enables actor group flag. */
u32 ScriptCmd_SetActorGroupFlag_020b3030(u32 context)
{
    s32 actor;

    actor = func_ov021_020b0374();
    actor = func_ov021_020b0250(context, *(u32 *)(actor + 4));
    if (actor != 0) {
        func_ov001_020969e0(actor, 1);
    }
    return 0;
}
