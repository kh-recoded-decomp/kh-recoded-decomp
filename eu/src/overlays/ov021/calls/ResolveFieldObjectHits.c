#include "src/overlays/ov001/FieldObjectCallbacks.h"
#include "src/overlays/ov021/HitFacingFilter.h"

typedef struct FieldHitOptions {
    u8 unknown00[0x10];
    u8 unknown10;
    u8 unknown11;
    u8 unknown12[2];
    VecFx32 velocity;
    s32 mode;
    u16 flags;
    u8 damage;
} FieldHitOptions;

typedef struct FieldHitScan {
    u32 flags;
    u32 unknown04;
    s32 kind;
    VecFx32 point;
    u8 unknown18[0xd4 - 0x18];
    s32 state;
    FieldObject *pending;
} FieldHitScan;

typedef char FieldHitVelocityOffset[(u32)&((FieldHitOptions *)0)->velocity == 0x14 ? 1 : -1];
typedef char FieldHitModeOffset[(u32)&((FieldHitOptions *)0)->mode == 0x20 ? 1 : -1];
typedef char FieldHitFlagsOffset[(u32)&((FieldHitOptions *)0)->flags == 0x24 ? 1 : -1];
typedef char FieldHitDamageOffset[(u32)&((FieldHitOptions *)0)->damage == 0x26 ? 1 : -1];
typedef char FieldScanPointOffset[(u32)&((FieldHitScan *)0)->point == 0xc ? 1 : -1];
typedef char FieldScanStateOffset[(u32)&((FieldHitScan *)0)->state == 0xd4 ? 1 : -1];
typedef char FieldScanPendingOffset[(u32)&((FieldHitScan *)0)->pending == 0xd8 ? 1 : -1];
typedef char FieldHitContactSize[sizeof(FieldObjectHitContact) == 0x18 ? 1 : -1];
typedef char FieldHitMessageSize[sizeof(FieldObjectHitMessage) == 0x1c ? 1 : -1];

extern VecFx32 ComputeKnockbackVector(HitFacingRecord *attack,
                                     FieldHitOptions *options,
                                     VecFx32 *position);
extern void ScaleVecFx32(fx32 scale, const VecFx32 *source, VecFx32 *destination);
extern VecFx32 GetShapeCenter(const void *shape);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *destination);
extern BOOL IsObjectIdle(FieldHitOptions *options);

static inline BOOL ResolveFieldObjectHitList(u8 element, HitFacingRecord *attack,
                                              FieldHitOptions *options,
                                              FieldHitScan *scan)
{
    FieldObject *object = scan->pending;
    BOOL done = FALSE;
    VecFx32 center;
    VecFx32 centerCopy;
    VecFx32 offset;
    FieldObjectHitMessage message;
    FieldObjectHitContact contact;

    for (; object != NULL && done != TRUE; object = object->next) {
        BOOL hit = FieldObject_QueryHit(object, attack, &contact);
        if (hit) {
            hit = IsHitWithinFacingAndHeight(attack, (HitFacingSample *)&contact,
                                             FieldObject_GetPosition(object));
        }
        if (hit) {
            if (options != NULL) {
                message.direction = ComputeKnockbackVector(
                    attack, options, FieldObject_GetPosition(object));
                message.element = element;
                message.reserved0d = 0;
                message.damage = options->damage;
                message.unknown14 = options->unknown10;
                message.unknown18 = options->unknown11;
                scan->flags = FieldObject_ApplyHit(object, &message);
            }
            scan->kind = 2;
            ScaleVecFx32(contact.distance, &contact.direction, &offset);
            center = GetShapeCenter(attack);
            centerCopy = center;
            VEC_Add(&centerCopy, &offset, &scan->point);
            if (options != NULL && !IsObjectIdle(options)) {
                scan->flags &= ~1;
            }
            done = TRUE;
        }
    }
    scan->pending = object;
    return object == NULL;
}

/* Process one accepted hit and retain the remaining field-object scan cursor. */
BOOL ResolveFieldObjectHits(int element, HitFacingRecord *attack,
                            FieldHitOptions *options, FieldHitScan *scan)
{
    return ResolveFieldObjectHitList((u8)element, attack, options, scan);
}
