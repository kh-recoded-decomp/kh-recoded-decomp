#include "nitro/types.h"

typedef struct {
    u8 pad[0x80];
    u16 state;
} Actor;

extern Actor *func_02036240(u32 actorId);
extern void WriteSessionPackedBits_0206459c(int bitIndex, u32 width, u32 value);

BOOL RecordPlayerStateFlags_0208eef0(void) {
    Actor *player = func_02036240(0);
    if ((s32)player->state < (s32)0x8000) {
        WriteSessionPackedBits_0206459c(0x3629, 1, TRUE);
    } else {
        WriteSessionPackedBits_0206459c(0x3629, 1, FALSE);
    }
    WriteSessionPackedBits_0206459c(0x362a, 1, 1);
    return TRUE;
}
