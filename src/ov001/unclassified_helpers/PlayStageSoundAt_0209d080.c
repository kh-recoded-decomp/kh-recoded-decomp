#include "nitro/types.h"
#include "nitro/fx_types.h"

extern BOOL Session_Exists_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern BOOL func_ov001_020645c8(u32 value);
extern u32 func_0204da8c(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);

u32 PlayStageSoundAt_0209d080(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags)
{
    s32 sessionState;

    if (seqArcId == 0 && soundId == 0) {
        return 0;
    }
    if (Session_Exists_02063a24()) {
        sessionState = func_ov001_02063a38();
    } else {
        sessionState = 0;
    }
    if (sessionState == 6 && func_ov001_020645c8(0x379d)) {
        if (seqArcId == 0) {
            if (soundId == 0x25) {
                return 0;
            }
            if (soundId == 0x26) {
                return 0;
            }
        }
        if (seqArcId == 0xd0 && soundId == 7) {
            return 0;
        }
    }
    return func_0204da8c(seqArcId, soundId, position, flags);
}
