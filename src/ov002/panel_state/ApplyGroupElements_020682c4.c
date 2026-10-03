#include "nitro/types.h"

typedef struct ElementGroups {
    u8 pad_000[0x1d4];
    u8 members[44][16];
    u8 counts[44];
} ElementGroups;

extern void func_0204f378(void *panel, int index, int value);

void ApplyGroupElements_020682c4(void *panel, ElementGroups *groups, int group, int value)
{
    int i;
    for (i = 0; i < groups->counts[group]; i++) {
        func_0204f378(panel, groups->members[group][i], value);
    }
}
