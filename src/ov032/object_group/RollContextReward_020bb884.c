#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    u16 chances[4];
    u8 pad_1c[0x54];
    u8 rewards[4];
} RewardContext;

extern struct { RewardContext *context; } contextData_020c0060;
extern unsigned int func_0202a9d0(unsigned int range);

int RollContextReward_020bb884(int mode)
{
    int roll;
    int i;

    if (mode == 0) {
        return mode;
    }
    roll = func_0202a9d0(1000);
    if (mode == 1) {
        for (i = 0; i < 3; i++) {
            if (contextData_020c0060.context->chances[i] > roll) {
                return contextData_020c0060.context->rewards[i];
            }
            roll -= contextData_020c0060.context->chances[i];
        }
    } else if (mode == 2) {
        if (contextData_020c0060.context->chances[3] > roll) {
            return contextData_020c0060.context->rewards[3];
        }
    }
    return 0;
}
