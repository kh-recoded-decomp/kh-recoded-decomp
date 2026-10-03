#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    s16 ids[3];
    u8 pad_0E[2];
    int values[3];
    u8 pad_1C[4];
    int current;
    u8 pad_24[8];
} TargetSet;

extern void MIi_CpuFill8_01ff8830(void *dest, u8 data, u32 size);

void ResetTargetSet_020adf90(TargetSet *set) {
    int i;

    MIi_CpuFill8_01ff8830(set, 0, sizeof(TargetSet));
    for (i = 0; i < 3; i++) {
        set->ids[i] = -1;
        set->values[i] = -1;
    }
    set->current = -1;
}
