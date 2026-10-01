#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct SurfaceInfo {
    u8 pad[0x14];
    VecFx16 normal;
} SurfaceInfo;

typedef struct SurfaceRecord {
    SurfaceInfo *info;
    int kind;
} SurfaceRecord;

typedef struct FacingActor {
    u8 pad[0x20];
    VecFx32 direction;
} FacingActor;

extern s32 ContainsMatchingEntry_02034900(SurfaceRecord *self, u32 kind);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);

static inline VecFx32 ToVecFx32(const VecFx16 *source) {
    VecFx32 result;
    result.x = source->x;
    result.y = source->y;
    result.z = source->z;
    return result;
}

BOOL CheckSurfaceFacing_02085734(SurfaceRecord *record, int unused, FacingActor *actor, BOOL checkFacing) {
    VecFx32 normal;

    if (ContainsMatchingEntry_02034900(record, 9)) {
        return FALSE;
    }
    if (record->kind == 1 && checkFacing) {
        normal = ToVecFx32(&record->info->normal);
        if (AbsDotProduct_0204a96c(&actor->direction, &normal) < 0x10) {
            return FALSE;
        }
    }
    return TRUE;
}
