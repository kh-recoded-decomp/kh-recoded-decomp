#include "nitro/types.h"

typedef struct {
    u8 pad_0000[0xCFE0];
    u32 phase;
} Ov101State;

extern Ov101State *data_ov101_020c5920;

u32 GetStatePhase(void)
{
    return data_ov101_020c5920->phase;
}
