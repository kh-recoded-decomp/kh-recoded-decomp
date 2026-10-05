#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactNode {
    u8 type;
} ContactNode;

typedef struct ContactObject {
    u8 pad_00[0x60];
    ContactNode *node;
    u8 pad_64[0xc];
    VecFx32 anchor;
} ContactObject;

typedef struct ContactLink {
    ContactObject *object;
    int type;
} ContactLink;

typedef struct ContactOwner {
    u8 pad_00[0xd];
    u8 hasRestPoint;
    u8 pad_0E[0x36];
    VecFx32 restPoint;
    u8 pad_50[0x18];
    ContactLink link;
} ContactOwner;

typedef struct ContactSource {
    ContactOwner *owner;
    int kind;
} ContactSource;

typedef struct ContactResult {
    VecFx32 position;
    BOOL grounded;
} ContactResult;

extern VecFx32 data_02053438;
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVecFx32InPlace_0204a5e4(VecFx32 *vec, fx32 scale);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline VecFx32 Difference(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Subtract_01ff9e3c(a, b, &result);
    return result;
}

static inline VecFx32 Scaled(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace_0204a5e4(&vec, scale);
    return vec;
}

static inline VecFx32 Negated(const VecFx32 *vec)
{
    VecFx32 result = *vec;
    NegateVecFx32_0204aa40(&result);
    return result;
}

void ResolveFieldContact_020a4574(ContactSource *source, VecFx32 *normal, ContactResult *result)
{
    ContactLink *link;
    VecFx32 *anchor;
    ContactNode *node;
    VecFx32 offset;
    VecFx32 push;
    VecFx32 back;
    fx32 dot;

    if (source->kind == 4 && (link = &source->owner->link)->type == 8) {
        node = link->object->node;
        if (node != NULL && node->type != 0) {
            if (node->type != 3) {
                return;
            }
            anchor = &link->object->anchor;
            offset = Difference(&result->position, anchor);
            dot = VEC_DotProduct_01ff9e6c(&offset, normal);
            push = Scaled(Scaled(*normal, dot), 0x400);
            back = Negated(&push);
            VEC_Add_01ff9e0c(anchor, &back, &result->position);
            VEC_Add_01ff9e0c(anchor, &push, anchor);
            return;
        }
    }
    if (normal->y > 0xf80) {
        result->grounded = TRUE;
        if (source->kind == 4 && source->owner->hasRestPoint) {
            result->position = source->owner->restPoint;
        } else {
            result->position = data_02053438;
        }
    }
}
