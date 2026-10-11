#include "nitro/types.h"

typedef struct PathPoint {
    s16 x;
    s16 y;
} PathPoint;

typedef struct PathLink {
    u32 value;
    int unk04;
    PathPoint **points;
    s8 kind;
    s8 pointCount;
    s8 unk0e;
    s8 flagA : 1;
    s8 flagB : 1;
    s8 flagPad : 6;
} PathLink;

typedef struct PathGroup {
    s16 id;
    s16 linkCount;
    PathLink **links;
} PathGroup;

typedef struct PathGraph {
    int groupCount;
    PathGroup *groups;
    int linkCount;
    PathLink *links;
    PathPoint *points;
    void *callback14;
    void *callback18;
    u8 selection;
    u8 pad1d[3];
    int unk20;
    int unk24;
    int unk28;
    int unk2c;
    int unk30;
    int unk34;
    u8 pad38[4];
} PathGraph;

typedef struct PathFileHeader {
    int groupCount;
    int linkCount;
    int linkOffset;
    int pointCount;
    int pointOffset;
} PathFileHeader;

typedef struct PathFilePoint {
    int x;
    int y;
} PathFilePoint;

typedef struct PathFileLink {
    u32 value;
    int flag;
    int kind;
    int closed;
    int pointCount;
} PathFileLink;

typedef struct PathFileGroup {
    int id;
    int linkCount;
} PathFileGroup;

extern u8 data_020608c8;
extern u32 data_ov021_020b5604;

extern u8 *func_0204f768(u32 selection);
extern void func_01ff8830(void *dst, int value, u32 size);
extern int func_02025658(void);
extern BOOL func_ov001_020645c8(int flagId);
extern void *func_0202c48c(u32 fileId, u32 heapId);
extern void *NNSi_FndAllocFromDefaultHeap_0202a178(u32 size);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *block);
extern void func_ov021_020a7c60(void);
extern void func_ov021_020a7c88(void);

#define GRAPH_FILE_ID(kind) (((((data_ov021_020b5604 + 0x8000) & 0xfffffc) << 7) | 0x80000000) | ((kind) & 0x1ff))

void LoadPathGraph_020a7cc8(PathGraph *graph, u32 kind, u32 selection)
{
    int offset;
    int linkOffset;
    PathFileHeader *header;
    PathFilePoint *srcPoint;
    PathFileLink *srcLink;
    PathFileGroup *srcGroup;
    PathLink *link;
    PathGroup *group;
    int *indices;
    int i;
    int j;

    func_0204f768(selection);
    func_01ff8830(graph, 0, sizeof(PathGraph));
    graph->unk24 = 0;
    graph->selection = selection;
    graph->callback14 = func_ov021_020a7c60;
    graph->unk28 = -1;
    graph->unk2c = -1;
    graph->unk34 = -1;
    graph->unk30 = -1;
    graph->unk20 = -1;
    graph->callback18 = func_ov021_020a7c88;
    if (kind == 0) {
        if (func_02025658() == 2 && (data_020608c8 > 1 || func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x3609 + 1))) {
            kind = 4;
        }
        header = func_0202c48c(GRAPH_FILE_ID(kind), 0x11);
    } else {
        header = func_0202c48c(GRAPH_FILE_ID(kind), 0x11);
    }
    srcPoint = (PathFilePoint *)((u8 *)header + header->pointOffset);
    graph->points = NNSi_FndAllocFromDefaultHeap_0202a178(header->pointCount * sizeof(PathPoint));
    for (i = 0; i < header->pointCount; i++) {
        graph->points[i].x = srcPoint->x;
        graph->points[i].y = srcPoint->y;
        srcPoint++;
    }
    graph->links = NNSi_FndAllocFromDefaultHeap_0202a178(header->linkCount * sizeof(PathLink));
    graph->linkCount = header->linkCount;
    linkOffset = header->linkOffset;
    for (i = 0; i < header->linkCount; i++) {
        srcLink = (PathFileLink *)((u8 *)header + linkOffset);
        link = &graph->links[i];
        graph->links[i].value = *(u32 *)((u8 *)header + linkOffset);
        link->flagA = srcLink->flag;
        link->kind = srcLink->kind;
        link->flagB = srcLink->closed == 0;
        link->pointCount = srcLink->pointCount;
        link->unk04 = 0;
        link->unk0e = -1;
        linkOffset += 0x14;
        link->points = NNSi_FndAllocFromDefaultHeap_0202a178(srcLink->pointCount * sizeof(PathPoint *));
        if (graph->links[i].pointCount > 0) {
            indices = (int *)(srcLink + 1);
            for (j = 0; j < graph->links[i].pointCount; j++) {
                link->points[j] = &graph->points[indices[j]];
                linkOffset += 4;
            }
        }
    }
    offset = sizeof(PathFileHeader);
    graph->groups = NNSi_FndAllocFromDefaultHeap_0202a178(header->groupCount * sizeof(PathGroup));
    graph->groupCount = header->groupCount;

    for (i = 0; i < header->groupCount; i++) {
        srcGroup = (PathFileGroup *)((u8 *)header + offset);
        group = &graph->groups[i];
        graph->groups[i].id = srcGroup->id;
        group->linkCount = srcGroup->linkCount;
        group->links = NNSi_FndAllocFromDefaultHeap_0202a178(group->linkCount * sizeof(PathLink *));
        offset += 8;
        j = 0;
        if (group->linkCount > 0) {
            indices = (int *)(srcGroup + 1);
            for (; j < group->linkCount; j++) {
                group->links[j] = &graph->links[indices[j]];
                offset += 4;
            }
        }
    }
    NNSi_FndFreeFromDefaultHeap_0202a1c4(header);
}
