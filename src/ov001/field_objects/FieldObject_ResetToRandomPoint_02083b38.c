#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct VariantEntry {
    VecFx32 *points;
    s8 pointCount;
    s8 savedBits;
    u8 pad_06[2];
} VariantEntry;

typedef struct FieldBody {
    u8 pad_000[0xb8];
    VecFx32 position;
    u8 pad_0c4[0x11c - 0xc4];
    u8 collision[0x15c - 0x11c];
    int collisionId;
} FieldBody;

typedef struct FieldObject {
    u8 pad_00[0xc];
    FieldBody *body;
    u8 pad_10[0x40 - 0x10];
    VecFx32 position;
    u8 pad_4c[2];
    u16 flags;
    u8 pad_50[0xc];
    int timer;
    VariantEntry *variants;
    VecFx32 velocity;
    u8 pad_70[0x7d - 0x70];
    s8 variantIndex;
    u8 pad_7e;
    s8 pointIndex;
    s8 startPoint;
} FieldObject;

extern signed char GetCtxModeByte_02068084(void);
extern unsigned int random_next_scaled_0202aa04(unsigned int upperBound);
extern void SetCollisionObjectPosition_02033f48(void *object, const VecFx32 *position);
extern BOOL DetachFromLeaderQuadTree_020836d8(FieldObject *object);
extern void FieldObject_AdvanceRandomVariant_020846a4(FieldObject *object);

void FieldObject_ResetToRandomPoint_02083b38(FieldObject *object, int reset)
{
    if (reset && GetCtxModeByte_02068084() == 7) {
        VecFx32 velocity;
        object->timer = 0;
        object->flags |= 0x10;
        object->pointIndex = random_next_scaled_0202aa04(object->variants[object->variantIndex].pointCount);
        object->startPoint = object->pointIndex;
        object->position = object->variants[object->variantIndex].points[object->pointIndex];
        velocity.x = 0;
        velocity.y = 0;
        velocity.z = FX32_ONE;
        object->velocity = velocity;
        if (object->body->collisionId != -1) {
            SetCollisionObjectPosition_02033f48(object->body->collision, &object->position);
        }
        object->body->position = object->position;
    }
    if (!reset && DetachFromLeaderQuadTree_020836d8(object) && GetCtxModeByte_02068084() != 7) {
        FieldObject_AdvanceRandomVariant_020846a4(object);
    }
}
