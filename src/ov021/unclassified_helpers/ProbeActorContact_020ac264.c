#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x1a4];
} QueryWorkspace;

typedef struct {
    void *func;
    void *arg;
} QueryFilter;

typedef struct {
    u32 words[0x14];
    QueryFilter filter;
    u32 tail[2];
} CollisionQuery;

typedef struct {
    u8 pad_000[0x194];
    u8 kind;
} ContactOwner;

typedef struct {
    u8 pad_00[0x14];
    ContactOwner *owner;
    u8 pad_18[0x54];
    int state;
} ContactObject;

typedef struct {
    u32 unk_00;
    u32 wall;
    u32 floor;
    u32 ceiling;
    ContactObject *object;
    u32 rest[0x29];
} ContactHit;

typedef struct {
    u32 unk_00;
    int kind;
    BOOL found;
    VecFx32 center;
    u32 unk_18;
    ContactHit hit;
} ContactResult;

extern void *func_02036240(u16 id);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, s32 unk44);
extern ContactHit *SweepWorldCollision_020364a0(CollisionQuery *query);
extern VecFx32 GetShapeCenter_0203b43c(const void *shape);
extern void func_ov021_020a9230(void);

BOOL ProbeActorContact_020ac264(int actorId, void *shape, ContactResult *result) {
    BOOL found = FALSE;
    int kind = 0;
    ContactHit *hit;
    QueryFilter filter;
    VecFx32 center;
    CollisionQuery sweep;
    QueryWorkspace workspace;
    CollisionQuery query;
    if (result != NULL) {
        result->kind = found;
        result->found = found;
    }
    CollisionQuery_Init_02034c74(&query, 0, func_02036240(actorId), 0xf, 0, 1, shape, &workspace, 0);
    sweep = query;
    filter.func = func_ov021_020a9230;
    filter.arg = NULL;
    sweep.filter = filter;
    hit = SweepWorldCollision_020364a0(&sweep);
    if (hit != NULL) {
        if (hit->floor != 0) {
            kind = 1;
            found = TRUE;
        } else if (hit->wall != 0) {
            kind = 2;
            found = TRUE;
        } else if (hit->ceiling != 0) {
            kind = 3;
            found = TRUE;
        } else if (hit->object != NULL && hit->object->owner->kind == 1 && (u32)(hit->object->state - 0x19) <= 1) {
            kind = 4;
            found = TRUE;
        }
        if (result != NULL && found) {
            result->found = TRUE;
            result->kind = kind;
            center = GetShapeCenter_0203b43c(shape);
            result->center = center;
            result->hit = *hit;
        }
    }
    return found;
}
