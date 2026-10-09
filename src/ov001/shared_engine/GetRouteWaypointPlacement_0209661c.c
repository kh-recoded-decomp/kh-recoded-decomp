#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Placement {
    VecFx32 position;
    fx32 value;
    u16 segment;
} Placement;

typedef struct RoutePoint {
    u32 start;
    u32 nameIndex;
    VecFx32 offset;
    u8 pad_14[4];
    fx32 value;
    u8 pad_1c[8];
    u8 forced;
} RoutePoint;

typedef struct RouteSegment {
    u32 start;
    u32 length;
} RouteSegment;

typedef struct RouteLink {
    u8 pad_00[0x1e];
    u16 segmentIndex;
} RouteLink;

typedef struct RouteHeader {
    u8 pad_00[0x94];
    u32 pointCount;
    u32 pointStride;
    u8 *points;
    u8 pad_a0[0x54];
    u32 segmentCount;
    u32 segmentStride;
    u8 *segments;
    u8 pad_100[0x14];
    u32 linkCount;
    u32 linkStride;
    u8 *links;
} RouteHeader;

typedef struct RouteContext {
    u8 pad_00[8];
    RouteHeader *header;
} RouteContext;

typedef struct StageEntry {
    u32 pad_00;
    RouteContext *route;
} StageEntry;

typedef struct StageActor {
    u8 pad_000[0xb8];
    VecFx32 anchor;
    u8 pad_0c4[0x58];
    u8 surface[0x16c];
    u16 flagsLow : 4;
    u16 pinned : 1;
    u16 flagsHigh : 11;
    u16 pad_28a;
    u16 linkSlot : 3;
    u16 linkFlags : 13;
    u8 pad_28e[0x32];
    VecFx32 position;
} StageActor;

typedef struct PartySlot {
    u8 pad_00[0x18];
    Placement placement;
} PartySlot;

typedef struct RouteActor {
    s32 type;
    u16 pad_04;
    u16 flagsLow : 11;
    u16 disabled : 1;
    u16 flagsHigh : 4;
    u16 pad_08;
    u8 state;
    u8 pad_0b;
    u8 pad_0c;
    u8 doneMask;
    u16 kind;
    u16 targetId;
    u16 pad_12;
    s16 entryId;
    u8 pad_16[0x19a];
    s32 cooldown;
} RouteActor;

extern StageEntry *GetStageEntry_0209c074(int id);
extern StageActor *GetStageActor_0209c040(int id);
extern StageActor *GetLinkedStageActor_0209c2f0(StageActor *owner);
extern u16 GetStageRowIndex_0209c228(int offset);
extern PartySlot *FindPartySlotById_0209d19c(u32 memberId);
extern fx32 Surface_GetKindValue_02034c24(void *surface);
extern int Session_Exists_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern s32 func_ov001_0208f018(RouteContext *ctx, int index);
extern int FindActorResourceIndexByName_02091248(StageActor *actor, const char *name);
extern void GetNodePosition_02091600(StageActor *owner, u32 nodeId, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline s32 GetSessionMode(void)
{
    return Session_Exists_02063a24() ? func_ov001_02063a38() : 0;
}

static inline u32 Entry_GetPointCount(StageEntry *entry)
{
    if (entry == NULL) {
        return 0;
    }
    if (entry->route == NULL) {
        return 0;
    }
    return entry->route->header->pointCount;
}

static inline u32 Entry_GetSegmentCount(StageEntry *entry)
{
    if (entry == NULL) {
        return 0;
    }
    if (entry->route == NULL) {
        return 0;
    }
    return entry->route->header->segmentCount;
}

static inline u32 Entry_GetLinkCount(StageEntry *entry)
{
    if (entry == NULL) {
        return 0;
    }
    if (entry->route == NULL) {
        return 0;
    }
    return entry->route->header->linkCount;
}

static inline RoutePoint *Entry_GetPoint(StageEntry *entry, int index)
{
    u32 count;
    RouteHeader *header;
    u8 *points;

    if (entry == NULL) {
        return NULL;
    }
    if (entry->route == NULL) {
        return NULL;
    }
    count = Entry_GetPointCount(entry);
    header = entry->route->header;
    points = header->points;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (RoutePoint *)(points + index * header->pointStride);
}

static inline RouteSegment *Entry_GetSegment(StageEntry *entry, u16 index)
{
    u32 count;
    RouteHeader *header;
    u8 *segments;

    if (entry == NULL) {
        return NULL;
    }
    if (entry->route == NULL) {
        return NULL;
    }
    count = Entry_GetSegmentCount(entry);
    header = entry->route->header;
    segments = header->segments;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (RouteSegment *)(segments + index * header->segmentStride);
}

static inline RouteLink *Entry_GetLink(StageEntry *entry, u16 index)
{
    u32 count;
    RouteHeader *header;
    u8 *links;

    if (entry == NULL) {
        return NULL;
    }
    if (entry->route == NULL) {
        return NULL;
    }
    count = Entry_GetLinkCount(entry);
    header = entry->route->header;
    links = header->links;
    if (count == 0) {
        return NULL;
    }
    if (index >= count) {
        return NULL;
    }
    return (RouteLink *)(links + index * header->linkStride);
}

BOOL GetRouteWaypointPlacement_0209661c(RouteActor *actor, int index, Placement *out)
{
    RoutePoint *point = NULL;
    StageActor *current;
    StageActor *stageActor;
    StageEntry *entry;
    PartySlot *slot;
    RouteSegment *segment;
    s32 mode;
    u16 count;
    u32 segmentIndex;
    u16 linkSlot;
    int node;

    entry = GetStageEntry_0209c074(actor->entryId);
    if (entry == NULL) {
        return FALSE;
    }
    if (actor->disabled || actor->type == 0xb) {
        return FALSE;
    }
    if (actor->kind == 99) {
        slot = FindPartySlotById_0209d19c(GetStageRowIndex_0209c228((int)actor));
        if (slot != NULL) {
            *out = slot->placement;
            return TRUE;
        }
    }
    if (actor->targetId == 0) {
        return FALSE;
    }
    stageActor = GetStageActor_0209c040((s16)actor->targetId);
    if (stageActor == NULL) {
        return FALSE;
    }
    if (actor->type == 2 && actor->cooldown > 0) {
        return FALSE;
    }
    if (stageActor != NULL && out != NULL) {
        out->position = stageActor->position;
        out->value = Surface_GetKindValue_02034c24(stageActor->surface);
        mode = 0;
        out->segment = 0;
        if (Session_Exists_02063a24()) {
            mode = func_ov001_02063a38();
        }
        if (mode == 4) {
            out->position.z = 0;
        }
    }
    count = Entry_GetPointCount(entry);
    if (count == 0) {
        return FALSE;
    }
    if (out != NULL) {
        out->segment = (index + 1) % count;
    }
    if (actor->doneMask & (1 << index)) {
        return FALSE;
    }
    for (current = stageActor; current != NULL; current = GetLinkedStageActor_0209c2f0(current)) {
        linkSlot = current->linkSlot;
        segmentIndex = 0;
        if (linkSlot != 0) {
            segmentIndex = (u32)Entry_GetLink(entry, linkSlot - 1);
            if (segmentIndex == 0) {
                segment = NULL;
                goto checkSegment;
            }
            segmentIndex = ((RouteLink *)segmentIndex)->segmentIndex;
        }
        segment = Entry_GetSegment(entry, segmentIndex);
    checkSegment:
        if (segment == NULL || segment->length == 0) {
            break;
        }
        if (index < segment->start + segment->length) {
            point = Entry_GetPoint(entry, index);
            out->position = current->anchor;
            if (GetSessionMode() == 4) {
                out->position.z = 0;
            }
            break;
        }
    }
    if (out != NULL && point != NULL && current != NULL) {
        if (actor->state != 4 && !stageActor->pinned && point->forced == 0) {
            return FALSE;
        }
        out->value = point->value;
        if (point->nameIndex != 0) {
            node = FindActorResourceIndexByName_02091248(current, (const char *)func_ov001_0208f018(entry->route, point->nameIndex));
            if (node != 0xffff) {
                GetNodePosition_02091600(current, (u16)node, &out->position);
            }
        }
        VEC_Add_01ff9e0c(&out->position, &point->offset, &out->position);
        if (GetSessionMode() == 4) {
            out->position.z = 0;
        }
    }
    return TRUE;
}
