#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 min[3];
    fx32 max[3];
} Box;

typedef struct {
    u32 words[24];
} MeshQuery;

typedef struct {
    u8 pad_000[0x10];
    u8 anchor[0x160 - 0x10];
    VecFx32 velocity;
    Box bounds;
} ProbeOwner;

typedef struct {
    u8 pad_00[0xc];
    ProbeOwner *owner;
    u8 pad_10[0xa0 - 0x10];
    Box cached;
} WorldProbe;

extern BOOL CachedBounds_NeedsRefresh_02035044(Box *cached, const Box *query);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void AttachToAnchor_02034cec(MeshQuery *self, u16 kind, void *anchor, u8 flag, Box *bounds, int mode);
extern void TestQueryAgainstWorldMeshes_020364d8(MeshQuery *query);

void ProbeWorldAlongVelocity_02085278(WorldProbe *probe, int mode) {
    MeshQuery request;
    MeshQuery query;
    Box bounds;
    VecFx32 delta;
    VecFx32 dir;
    Box moved;

    bounds = probe->owner->bounds;
    if (CachedBounds_NeedsRefresh_02035044(&probe->cached, &bounds)) {
        dir = probe->owner->velocity;
        func_01ffaff4(&dir, &dir);
        ScaleVecFx32InPlace_0204a5e4(&dir, 0x2000);
        delta = dir;
        OffsetBoxByDelta_0203ac70(&bounds, &moved, &delta);
        probe->cached = moved;
        AttachToAnchor_02034cec(&query, 0, probe->owner->anchor, 11, &probe->cached, mode);
        request = query;
        TestQueryAgainstWorldMeshes_020364d8(&request);
    }
}
