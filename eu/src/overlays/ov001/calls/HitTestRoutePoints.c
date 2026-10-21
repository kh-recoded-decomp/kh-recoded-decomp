#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollBox {
    fx32 maxX;
    fx32 maxY;
    fx32 maxZ;
    fx32 minX;
    fx32 minY;
    fx32 minZ;
} CollBox;

typedef struct CollShape {
    void *data;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
    CollBox sweepBox;
} CollSweep;

typedef struct CollSphere {
    VecFx32 center;
    fx32 radius;
} CollSphere;

typedef struct CollHit CollHit;

typedef BOOL (*ShapeTestFn)(CollShape *shape, CollSweep *other, CollHit *hit, u32 flags);
typedef BOOL (*ShapeSweepFn)(CollShape *shape, CollSweep *other, CollHit *hit, u32 flags, VecFx32 *delta);

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
    u8 pad_000[0x10];
    u8 body[0x278];
    u16 flagsLow : 4;
    u16 pinned : 1;
    u16 flagsHigh : 11;
    u16 pad_28a;
    u16 linkSlot : 3;
    u16 linkFlags : 13;
    u8 pad_28e[0x8e];
    fx32 scale;
} StageActor;

typedef struct RouteActor {
    s32 type;
    u16 pad_04;
    u16 flagsLow : 11;
    u16 disabled : 1;
    u16 flagsHigh : 3;
    u16 intangible : 1;
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

extern ShapeTestFn gCollisionTestDispatch[][6];
extern ShapeSweepFn gCollisionSweepDispatch[][6];

extern StageActor *GetStageActor(int id);
extern StageEntry *GetStageEntry(int id);
extern StageActor *GetLinkedStageActor(StageActor *owner);
extern int func_ov001_02063a24(void);
extern s32 func_ov001_02063a38(void);
extern s32 func_ov001_0208f040(RouteContext *ctx, int index);
extern int FindActorResourceIndexByName(StageActor *actor, const char *name);
extern void GetNodePosition(StageActor *owner, u32 nodeId, VecFx32 *out);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Mul(fx32 a, fx32 b);
extern void MakeSphereShape(CollShape *shape, CollSphere *sphere, const VecFx32 *center, fx32 radius);
extern void NegateVecFx32(VecFx32 *vec);

enum {
    CONTACT_NONE,
    CONTACT_MOVING,
    CONTACT_RESTING
};

static inline s32 GetSessionMode(void)
{
    return func_ov001_02063a24() ? func_ov001_02063a38() : 0;
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

static inline RoutePoint *Entry_GetPoint(StageEntry *entry, u16 index)
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

/* Link slots are 1-based; 0 means the actor has no link. */
static inline RouteLink *Entry_GetSlotLink(StageEntry *entry, u16 slot)
{
    return Entry_GetLink(entry, slot - 1);
}

static inline BOOL BoxesOverlap(const CollBox *a, const CollBox *b)
{
    return a->maxX >= b->minX && a->minX <= b->maxX
        && a->maxZ >= b->minZ && a->minZ <= b->maxZ
        && a->maxY >= b->minY && a->minY <= b->maxY;
}

static inline BOOL IsZeroVec(const VecFx32 *vec)
{
    return vec->x == 0 && vec->y == 0 && vec->z == 0;
}

/* Test the hit spheres of the route points carried by the actor's stage model (and the models linked
 * to it) against `target`, as a sweep when `sweep` is set, and return one bit per point that hits.
 * Points already in the actor's done mask are skipped. */
u32 HitTestRoutePoints(RouteActor *actor, int slot, BOOL sweep, CollSweep *target, CollHit *hit)
{
    StageActor *stageActor;
    StageEntry *entry;
    StageActor *current;
    RouteSegment *segment;
    u32 hitMask;
    u32 pointIndex;
    u32 k;
    u32 segmentIndex;
    u16 linkSlot;
    BOOL allowed;

    if (slot >= 3) {
        return 0;
    }
    if (actor->targetId == 0) {
        return 0;
    }
    if (actor->intangible) {
        return 0;
    }
    allowed = FALSE;
    if (actor->type == 3) {
        allowed = TRUE;
    } else if (actor->type == 4) {
        allowed = TRUE;
    } else if (actor->type == 5) {
        allowed = TRUE;
    } else if (actor->type == 10) {
        allowed = TRUE;
    } else if (actor->type == 2 && actor->cooldown <= 0) {
        allowed = TRUE;
    }
    if (!allowed) {
        return 0;
    }
    stageActor = GetStageActor((s16)actor->targetId);
    entry = GetStageEntry(actor->entryId);
    if (entry == NULL) {
        return 0;
    }
    if (stageActor->body == NULL) {
        return 0;
    }
    pointIndex = 0;
    hitMask = 0;
    for (current = stageActor; current != NULL; current = GetLinkedStageActor(current)) {
        linkSlot = current->linkSlot;
        segmentIndex = 0;
        if (linkSlot != 0) {
            RouteLink *link = Entry_GetSlotLink(entry, linkSlot);

            if (link == NULL) {
                segment = NULL;
                goto checkSegment;
            }
            segmentIndex = link->segmentIndex;
        }
        segment = Entry_GetSegment(entry, segmentIndex);
    checkSegment:
        if (segment == NULL || segment->length == 0) {
            break;
        }
        if (pointIndex >= segment->start + segment->length) {
            continue;
        }
        for (k = 0; k < segment->length; k++, pointIndex++) {
            RoutePoint *point = Entry_GetPoint(entry, segment->start + k);
            int node;
            CollSphere sphere;
            CollShape shape;
            VecFx32 center;
            CollShape made;
            BOOL result;

            if (point == NULL) {
                continue;
            }
            if (!stageActor->pinned && point->forced == 0) {
                continue;
            }
            if ((1 << pointIndex) & actor->doneMask) {
                continue;
            }
            node = 0xffff;
            if (point->nameIndex != 0) {
                node = FindActorResourceIndexByName(current, (const char *)func_ov001_0208f040(entry->route, point->nameIndex));
            }
            GetNodePosition(current, (u16)node, &center);
            VEC_Add(&center, &point->offset, &center);
            if (GetSessionMode() == 4) {
                center.z = 0;
            }
            /* The point's value is its hit radius, scaled with the actor. */
            MakeSphereShape(&made, &sphere, &center, FX_Mul(point->value, current->scale));
            shape = made;
            if (!sweep) {
                if (BoxesOverlap(&shape.box, &target->shape.box)) {
                    result = gCollisionTestDispatch[shape.kind][target->shape.kind](&shape, target, hit, 0);
                } else {
                    result = FALSE;
                }
                if (result) {
                    hitMask |= (u16)(1 << pointIndex);
                }
            } else {
                int contact;
                VecFx32 negated;
                VecFx32 reversed;

                if (BoxesOverlap(&shape.box, &target->sweepBox)) {
                    if (IsZeroVec(&target->delta)) {
                        contact = CONTACT_RESTING;
                    } else {
                        negated = target->delta;
                        NegateVecFx32(&negated);
                        reversed = negated;
                        contact = CONTACT_MOVING;
                    }
                } else {
                    contact = CONTACT_NONE;
                }
                if (contact != CONTACT_NONE) {
                    result = contact == CONTACT_RESTING
                        ? gCollisionTestDispatch[shape.kind][target->shape.kind](&shape, target, hit, (target->shape.kind == 2 ? 2 : 0) | 8)
                        : gCollisionSweepDispatch[shape.kind][target->shape.kind](&shape, target, hit, 8, &reversed);
                } else {
                    result = FALSE;
                }
                if (result) {
                    hitMask |= (u16)(1 << pointIndex);
                }
            }
        }
    }
    return hitMask;
}
