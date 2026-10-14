#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct DirectionMatrix {
    VecFx32 forward;
    VecFx32 up;
    VecFx32 right;
} DirectionMatrix;

typedef struct GroupMemberWork {
    u8 pad_00[0x34];
    DirectionMatrix orientation;
    VecFx32 collisionOffset;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x32];
    u8 actorId;
} GroupObject;

typedef struct CollisionBox {
    VecFx32 center;
    VecFx32 halfExtents;
    DirectionMatrix axes;
    u8 flags;
} CollisionBox;

typedef struct BoxBounds {
    VecFx32 min;
    VecFx32 max;
} BoxBounds;

typedef struct CollisionState {
    CollisionBox *box;
    BoxBounds bounds;
    u32 shapeKind;
    VecFx32 delta;
    BoxBounds localBounds;
} CollisionState;

typedef struct ActorBody {
    u8 pad_000[0x130];
    CollisionState collision;
} ActorBody;

typedef void (*BoundsBuilder)(CollisionState *collision, BoxBounds *bounds);

extern GroupMemberWork *func_ov032_020bbc98(GroupObject *object);
extern ActorBody *ActorRegistry_GetEntityByIndex(int index);
extern fx32 FX_Sqrt(fx32 value);
extern u16 FX_Atan2Idx(fx32 y, fx32 x);
extern void BuildDirectionPitchMatrix(DirectionMatrix *matrix, const VecFx32 *direction, int pitch);
extern void MTX_MultVec33(const VecFx32 *vector, const DirectionMatrix *matrix, VecFx32 *result);
extern void VEC_Add(const VecFx32 *first, const VecFx32 *second, VecFx32 *result);
extern void OffsetBoxByDelta(const BoxBounds *source, BoxBounds *result, const VecFx32 *delta);
extern void UpdateBoxAxisAlignedFlag(CollisionBox *box);
extern const VecFx32 gGroupCollisionPivotOffset;
extern const VecFx32 gGroupCollisionPivotBase;
extern const VecFx32 gZeroVecFx32;
extern BoundsBuilder gCollisionBoundsDispatch[];

static inline BOOL IsDirectionXYZero(const VecFx32 *direction)
{
    BOOL zeroXY = FALSE;
    if (direction->x == 0 && direction->y == 0) {
        zeroXY = TRUE;
    }
    return zeroXY;
}

static inline BOOL IsDirectionZero(const VecFx32 *direction)
{
    BOOL zero = FALSE;
    if (IsDirectionXYZero(direction) && direction->z == 0) {
        zero = TRUE;
    }
    return zero;
}

void OrientGroupActorCollisionFromDirection(GroupObject *object, const VecFx32 *direction)
{
    GroupMemberWork *work = func_ov032_020bbc98(object);
    ActorBody *actor = ActorRegistry_GetEntityByIndex(object->actorId);

    if (!IsDirectionZero(direction)) {
        s64 horizontalX = direction->x;
        s64 horizontalSquare = (s64)direction->z * direction->z;
        fx32 horizontalLength;

        horizontalSquare += horizontalX * horizontalX;
        horizontalLength = FX_Sqrt((fx32)(horizontalSquare >> FX32_SHIFT));
        if (horizontalLength != 0) {
            VecFx32 localOffset;
            VecFx32 originOffset;
            int pitch = FX_Atan2Idx(direction->y, horizontalLength);

            BuildDirectionPitchMatrix(&work->orientation, direction, pitch);
            localOffset = gGroupCollisionPivotOffset;
            originOffset = gGroupCollisionPivotBase;
            MTX_MultVec33(&localOffset, &work->orientation, &localOffset);
            VEC_Add(&localOffset, &originOffset, &work->collisionOffset);
        }
    } else {
        work->collisionOffset = gZeroVecFx32;
    }
    actor->collision.box->axes = work->orientation;
    CollisionState *collision = &actor->collision;
    gCollisionBoundsDispatch[actor->collision.shapeKind](collision, &collision->bounds);
    OffsetBoxByDelta(&actor->collision.bounds, &actor->collision.localBounds, &actor->collision.delta);
    UpdateBoxAxisAlignedFlag(actor->collision.box);
}
