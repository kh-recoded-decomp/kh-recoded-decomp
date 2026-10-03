#include "nitro/types.h"

typedef struct {
    s32 id;
} NodeData;

typedef struct {
    u8 bytes[0x90];
} NodeRecord;

typedef struct {
    int count;
    s32 *ids;
} NodeIdList;

typedef struct {
    u8 pad_00[0x40];
    NodeIdList idList;
    u8 pad_48[0x24];
    NodeRecord *records;
    int recordCount;
} NodeOwner;

typedef struct {
    u8 pad_00[0x14];
    u32 layer;
} NodeSource;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern void ParseNodeRecord_020aa720(NodeRecord *node, u32 layer, NodeData *src);

void BuildNodeRecords_020ade6c(NodeOwner *owner, NodeSource *source, int unused, u32 *file)
{
    NodeIdList *idList = &owner->idList;
    u32 *offset;
    int count;
    NodeData **table;
    int i;
    int j;
    NodeData *found;

    owner->recordCount = idList->count;
    offset = file;
    owner->records = NNSi_FndAllocFromDefaultHeap_0202a178(idList->count * sizeof(NodeRecord));
    offset++;
    count = (u8)file[0];
    table = NNSi_FndAllocFromDefaultHeap_0202a178(count * sizeof(NodeData *));
    for (i = 0; i < count; i++) {
        table[i] = (NodeData *)((u8 *)file + *offset++);
    }
    for (i = 0; i < owner->recordCount; i++) {
        NodeRecord *record = &owner->records[i];
        found = NULL;
        for (j = 0; j < count; j++) {
            if (table[j]->id == idList->ids[i]) {
                found = table[j];
                break;
            }
        }
        ParseNodeRecord_020aa720(record, source->layer, found);
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(table);
}
