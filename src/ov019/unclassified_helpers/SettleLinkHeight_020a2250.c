#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct Box {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct SweepShape {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBox;
} SweepShape;

typedef struct BoxStorage {
    u8 data[0x40];
} BoxStorage;

typedef struct QueryWorkspace {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct QueryCallback {
    void *func;
    void *context;
} QueryCallback;

typedef struct CollisionQuery {
    u32 words[0x12];
    QueryCallback filter;
    u32 pad_50[2];
    QueryCallback post;
} CollisionQuery;

typedef struct LinkOwner {
    u8 pad_00[0x4c];
    VecFx32 size;
} LinkOwner;

typedef struct Actor {
    u8 pad_00[4];
    LinkOwner *owner;
    u8 *entity;
    u8 pad_0c[0x38 - 0x0c];
    VecFx32 position;
    u8 pad_44[0x5a - 0x44];
    u16 flags;
    u8 pad_5c[0x64 - 0x5c];
    fx32 baseHeight;
} Actor;

extern const VecFx32 data_ov019_020a365c;
extern void MTX_Identity33_01ff90ec(MtxFx33 *mtx);
extern void InitBoxShape_0203ad54(CollisionShape *shape, void *storage, const VecFx32 *center,
                                  const VecFx32 *halfExtents, const MtxFx33 *rotation);
extern void OffsetBoxByDelta_0203ac70(const s32 *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D,
                                         void *shape, QueryWorkspace *workspace, s32 unk44);
extern BOOL SweepWorldCollision_020364a0(CollisionQuery *query);
extern BOOL IsLinkTargetNextLink_020a1ff8(void *context, Actor *actor);
extern void UpdateLinkLimit_020a2034(void *context, void *unused, Actor *actor);
extern Actor *FindLiveNextLink_020a20e0(Actor *actor);
extern Actor *FindLivePrevLink_020a2098(Actor *actor);

static inline QueryCallback MakeCallback(void *func, void *context)
{
    QueryCallback callback;
    callback.func = func;
    callback.context = context;
    return callback;
}

void SettleLinkHeight_020a2250(Actor *self, BOOL sweep)
{
    Actor *next = NULL;
    LinkOwner *owner = self->owner;
    Actor *prev;

    self->baseHeight = self->position.y;
    if (sweep) {
        CollisionQuery sweepQuery;
        QueryWorkspace workspace;
        SweepShape shapeCopy;
        SweepShape shape;
        CollisionQuery query;
        MtxFx33 rotation;
        BoxStorage storage;
        VecFx32 center;
        VecFx32 extent;
        fx32 halfY;
        fx32 halfX;
        fx32 halfZ;

        center = self->position;
        center.y += 0xc01;
        halfZ = owner->size.z >> 1;
        halfY = owner->size.y >> 1;
        halfX = owner->size.x >> 1;
        extent.x = halfX;
        extent.y = halfY;
        extent.z = halfZ;
        MTX_Identity33_01ff90ec(&rotation);
        InitBoxShape_0203ad54(&shape.shape, &storage, &center, &extent, &rotation);
        shape.delta = data_ov019_020a365c;
        OffsetBoxByDelta_0203ac70(shape.shape.bounds, &shape.sweptBox, &shape.delta);
        shapeCopy = shape;
        CollisionQuery_Init_02034c74(&query, 0xf, self->entity + 0x10, 9, 1, 1, &shapeCopy, &workspace, 0);
        sweepQuery = query;
        sweepQuery.filter = MakeCallback(IsLinkTargetNextLink_020a1ff8, self);
        sweepQuery.post = MakeCallback(UpdateLinkLimit_020a2034, self);
        self->baseHeight = -0x1000;
        SweepWorldCollision_020364a0(&sweepQuery);
    } else {
        BOOL locked = FALSE;
        if ((self->flags & 0x100) && !(self->flags & 0x800)) {
            locked = TRUE;
        }
        if (!locked) {
            next = FindLiveNextLink_020a20e0(self);
        }
    }
    if (next != NULL) {
        self->baseHeight = (next->flags & 1) ? next->baseHeight + 0x1800 : next->position.y;
    }
    if (self->baseHeight != self->position.y) {
        self->flags |= 1;
        prev = FindLivePrevLink_020a2098(self);
        if (prev != NULL) {
            SettleLinkHeight_020a2250(prev, FALSE);
        }
    }
}
