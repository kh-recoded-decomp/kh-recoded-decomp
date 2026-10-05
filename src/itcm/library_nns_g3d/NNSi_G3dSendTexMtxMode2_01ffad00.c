#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TexMtxState {
    u32 flags;
    u8 pad_04[0x2c];
    fx32 scaleS;
    fx32 scaleT;
} TexMtxState;

typedef void (*TexMtxBuilder)(u32 *matrix, const TexMtxState *state);

extern TexMtxBuilder data_01ffa660[8];
extern void QueueOrSendGeometryCommand_01ffa37c(u32 op, const void *args, u32 numWords);

#pragma opt_propagation off
void NNSi_G3dSendTexMtxMode2_01ffad00(const TexMtxState *state) {
    u32 packet[19];
    u32 *args;

    if (state->flags & 8) {
        packet[0] = 0x101610;
    } else {
        packet[0] = 0x101810;
    }
    packet[1] = 3;
    packet[18] = 2;
    packet[16] = 0;
    packet[13] = 0;
    packet[12] = 0;
    packet[11] = 0;
    packet[10] = 0;
    packet[9] = 0;
    packet[8] = 0;
    packet[5] = 0;
    packet[4] = 0;
    packet[17] = 0x1000;
    data_01ffa660[state->flags & 7](&packet[2], state);
    if (state->scaleS != 0x1000) {
        packet[2] = (fx32)(((s64)state->scaleS * (fx32)packet[2]) >> 12);
        packet[3] = (fx32)(((s64)state->scaleS * (fx32)packet[3]) >> 12);
        packet[14] = (fx32)(((s64)state->scaleS * (fx32)packet[14]) >> 12);
    }
    if (state->scaleT != 0x1000) {
        packet[6] = (fx32)(((s64)state->scaleT * (fx32)packet[6]) >> 12);
        packet[7] = (fx32)(((s64)state->scaleT * (fx32)packet[7]) >> 12);
        packet[15] = (fx32)(((s64)state->scaleT * (fx32)packet[15]) >> 12);
    }
    args = packet;
    QueueOrSendGeometryCommand_01ffa37c(packet[0], args + 1, 0x12);
}
