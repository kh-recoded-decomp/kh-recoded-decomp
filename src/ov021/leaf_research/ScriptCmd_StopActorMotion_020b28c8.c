#include "nitro/types.h"

extern u32 g_data_020b55ec;
extern u32 func_ov001_020911b4();
extern u32 func_ov021_020b02b8();
extern u32 func_ov021_020b0374();

/* Leaf script command: stop actor motion. */
u32 ScriptCmd_StopActorMotion_020b28c8(u32 context)
{
    s32 actor;

    actor = func_ov021_020b0374();
    actor = func_ov021_020b02b8(context, *(u32 *)(actor + 4));
    if (actor == 0) {
        return 0;
    }
    func_ov001_020911b4(actor, 0, &g_data_020b55ec, 0);
    return 0;
}
