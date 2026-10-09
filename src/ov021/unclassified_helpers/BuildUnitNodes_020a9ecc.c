#include "nitro/types.h"

typedef struct {
    s16 id;
    u8 group;
    u8 pad_03[0x45];
    void *groupRecord;
    u8 pad_4C[0x44];
} NodeRecord;

typedef struct {
    NodeRecord *node;
    s32 id;
    s32 unk_08;
} NodeLink;

typedef struct {
    NodeLink *links[2];
    s32 linkCounts[2];
    u8 pad_10[0x10];
} NodeLinkTable;

typedef struct {
    NodeLink *links;
    s32 unk_04;
    s32 count;
} LinkColumn;

typedef struct {
    u8 pad_00[0x2c];
} GroupRecord;

typedef struct {
    GroupRecord *records;
    s32 count;
    s8 *groups;
} GroupRecordSet;

typedef struct {
    u8 pad_00[4];
    u8 layer;
    u8 pad_05[7];
    NodeLinkTable tables[2];
    NodeRecord *nodes;
    s32 nodeCount;
    GroupRecordSet groupSet;
} NodeGraph;

extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void ParseNodeRecord_020aa720(NodeRecord *node, u8 layer, s32 *src);
extern void InitUnitSharedRecords_020aa150(NodeGraph *graph, u32 arg1, s32 arg2, s32 *groups);

void BuildUnitNodes_020a9ecc(NodeGraph *graph, u32 arg1, s32 arg2, u32 *data)
{
    NodeLinkTable *table;
    s32 **records;
    int recordCount;
    u32 *offsets;
    int i;
    int j;
    int k;
    int m;
    int uniqueCount;
    BOOL found;
    s32 *record;
    NodeLink *link;
    NodeLink *wanted;
    NodeRecord *node;
    GroupRecordSet *groupSet;
    LinkColumn *linkColumn;
    LinkColumn *column;
    int row;
    int side;
    NodeLinkTable *linkTable;
    int col;
    NodeLink *nodeLink;
    NodeLink *existing;
    NodeRecord *candidate;
    NodeLink unique[64];
    s32 groups[17];

    offsets = data;
    recordCount = *offsets++ & 0xff;
    records = NNSi_FndAllocFromDefaultHeap_0202a178(recordCount * 4);
    for (i = 0; i < recordCount; i++) {
        records[i] = (s32 *)((u8 *)data + *offsets);
        offsets++;
    }
    uniqueCount = 0;
    for (i = 0; i < 17; i++) {
        groups[i] = -1;
    }
    for (side = 0; side < 2; side++) {
        table = &graph->tables[side];
        for (j = 0; j < 2; j++) {
            column = (LinkColumn *)&table->links[j];
            for (k = 0; k < column->count; k++) {
                link = &column->links[k];
                found = FALSE;
                for (m = 0; m < uniqueCount; m++) {
                    existing = &unique[m];
                    if (existing->id == link->id) {
                        found = TRUE;
                        break;
                    }
                }
                if (!found) {
                    unique[uniqueCount++] = *link;
                }
            }
        }
    }
    graph->nodeCount = uniqueCount;
    graph->nodes = NNSi_FndAllocFromDefaultHeap_0202a178(uniqueCount * sizeof(NodeRecord));
    for (i = 0; i < uniqueCount; i++) {
        node = &graph->nodes[i];
        wanted = &unique[i];
        record = NULL;
        for (m = 0; m < recordCount; m++) {
            if (wanted->id == *records[m]) {
                record = records[m];
                break;
            }
        }
        ParseNodeRecord_020aa720(node, graph->layer, record);
        for (m = 0; m < 16; m++) {
            if (groups[m] == -1) {
                groups[m] = node->group;
                break;
            }
            if (node->group == groups[m]) {
                break;
            }
        }
    }
    InitUnitSharedRecords_020aa150(graph, arg1, arg2, groups);
    groupSet = &graph->groupSet;
    for (i = 0; i < graph->nodeCount; i++) {
        node = &graph->nodes[i];
        for (m = 0; m < groupSet->count; m++) {
            if (node->group == groupSet->groups[m]) {
                node->groupRecord = &groupSet->records[m];
            }
        }
    }
    for (row = 0; row < 2; row++) {
        linkTable = &graph->tables[row];
        for (col = 0; col < 2; col++) {
            linkColumn = (LinkColumn *)&linkTable->links[col];
            for (k = 0; k < linkColumn->count; k++) {
                nodeLink = &linkColumn->links[k];
                for (m = 0; m < graph->nodeCount; m++) {
                    candidate = &graph->nodes[m];
                    if (candidate->id == nodeLink->id) {
                        nodeLink->node = candidate;
                        break;
                    }
                }
            }
        }
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(records);
}
