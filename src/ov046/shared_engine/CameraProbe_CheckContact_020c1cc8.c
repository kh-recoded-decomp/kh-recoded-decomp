#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactNormal {
    fx16 x;
    fx16 y;
    fx16 z;
} ContactNormal;

typedef struct ProbeShape {
    u8 pad_00[0x4];
    VecFx32 max;
    VecFx32 min;
    int kind;
} ProbeShape;

typedef struct CollisionOwner {
    u8 pad_00[0x14];
    ContactNormal normal;
    u8 pad_1a[0x24 - 0x1a];
    ProbeShape shape;
    u8 pad_44[0x28];
    int objectType;
} CollisionOwner;

typedef struct ContactRef {
    CollisionOwner *owner;
    int category;
} ContactRef;

typedef struct ContactQuery {
    u8 pad_00[0x4];
    VecFx32 direction;
    fx32 distance;
} ContactQuery;

typedef struct CameraProbe {
    u8 pad_00[0x10];
    ProbeShape shape;
    u32 hit : 1;
    s32 slowDown : 1;
    VecFx32 normal;
} CameraProbe;

typedef struct ProbeSource {
    VecFx32 *base;
    u8 pad_04[0x1c];
    VecFx32 offset;
} ProbeSource;

typedef BOOL (*ShapeTestFn)(ProbeShape *self, ProbeShape *other, void *hit, int flags);

extern ShapeTestFn data_020558a0[][6];
extern BOOL IsFacingContactNormal_020349d8(ContactRef *ref, const VecFx32 *direction);
extern void func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern fx32 AbsDotProduct_0204a96c(const VecFx32 *a, const VecFx32 *b);
extern s8 GetCtxModeByte_02068084(void);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SetShapePosition_0203afa0(ProbeShape *shape, const VecFx32 *position);

static inline VecFx32 GetContactNormal(const ContactNormal *src)
{
    VecFx32 normal;
    normal.x = src->x;
    normal.y = src->y;
    normal.z = src->z;
    return normal;
}

static inline BOOL TestShapeOverlap(ProbeShape *shape, ProbeShape *other)
{
    if (shape->max.x >= other->min.x && shape->min.x <= other->max.x &&
        shape->max.z >= other->min.z && shape->min.z <= other->max.z &&
        shape->max.y >= other->min.y && shape->min.y <= other->max.y) {
        return data_020558a0[shape->kind][other->kind](shape, other, NULL, 0);
    }
    return FALSE;
}

BOOL CameraProbe_CheckContact_020c1cc8(ContactRef *ref, ContactQuery *query, CameraProbe *probe, ProbeSource *source)
{
    VecFx32 forward;
    VecFx32 position;
    VecFx32 normal;
    VecFx32 normalized;
    VecFx32 sum;

    if (!IsFacingContactNormal_020349d8(ref, &query->direction)) {
        return FALSE;
    }
    func_01ffaff4(&source->offset, &normalized);
    forward = normalized;
    if (VEC_DotProduct_01ff9e6c(&forward, &query->direction) >= -0x80) {
        return FALSE;
    }
    if (AbsDotProduct_0204a96c(&query->direction, &probe->normal) > 0xffe) {
        return FALSE;
    }
    if (ref->category == 4) {
        if (GetCtxModeByte_02068084() != 5) {
            int type = ref->owner->objectType;
            if (type == 0x1e || type == 1 || type == 0x23) {
                VEC_Add_01ff9e0c(source->base, &source->offset, &sum);
                position = sum;
                SetShapePosition_0203afa0(&probe->shape, &position);
                if (!TestShapeOverlap(&probe->shape, &ref->owner->shape)) {
                    return FALSE;
                }
                probe->hit = TRUE;
            }
        }
    } else {
        normal = GetContactNormal(&ref->owner->normal);
        if (VEC_DotProduct_01ff9e6c(&normal, &source->offset) >= 0) {
            return FALSE;
        }
    }
    if (probe->slowDown) {
        if ((query->distance -= 0x80000) < 0) {
            query->distance = 0;
        }
    }
    return TRUE;
}


