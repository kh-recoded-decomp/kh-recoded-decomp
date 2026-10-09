#include "nitro/types.h"

typedef struct CommRequest {
    s8 kind;
    s8 channel;
    s16 value2;
    s16 value4;
} CommRequest;

typedef struct CommState {
    s16 channel;
    s16 value2;
    s16 value4;
    s16 phase;
    u8 kind;
    u8 pad_09[0x17];
    int result;
} CommState;

extern CommState *g_commState_020bb760;

void ApplyCommRequest_020bac30(const CommRequest *request)
{
    g_commState_020bb760->value2 = request->value2;
    g_commState_020bb760->value4 = request->value4;
    g_commState_020bb760->channel = request->channel;
    g_commState_020bb760->phase = 3;
    g_commState_020bb760->kind = request->kind;
    g_commState_020bb760->result = 0;
}
