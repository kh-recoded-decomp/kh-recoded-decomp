#include "nitro/types.h"

typedef struct {
    int count;
    u32 *nodes;
} PathTable;

typedef struct {
    u8 pad_00[0x88];
    PathTable *tables;
} PathSet;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void MIi_CpuCopy32_01ff8710(const void *src, void *dest, u32 size);

void SetPathTable_020a1ad4(PathSet *set, int index, int count, const u32 *nodes) {
    set->tables[index].count = count;
    set->tables[index].nodes = NNSi_FndAllocFromDefaultHeap_0202a178(count * 4);
    MIi_CpuCopy32_01ff8710(nodes, set->tables[index].nodes, count * 4);
}
