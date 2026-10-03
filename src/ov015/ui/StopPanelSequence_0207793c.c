#include "nitro/types.h"

typedef struct CursorState {
    u8 pad_00[0x5f];
    s8 sequencePlaying;
} CursorState;

extern CursorState *data_ov015_020812e0;
extern void StopSeqArcOrDefault_0204d960(int player, int seqArcNo, int fadeFrames);

void StopPanelSequence_0207793c(void)
{
    if (data_ov015_020812e0->sequencePlaying != 0) {
        StopSeqArcOrDefault_0204d960(2, 0xc, 0);
        data_ov015_020812e0->sequencePlaying = 0;
    }
}
