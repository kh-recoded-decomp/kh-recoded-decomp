/* Traverse collision candidates, resolve contact planes, and report the final contacts.
 * EU entry: 0x01ffb4f8. Object views below describe only the fields used here.
 */
#if defined(__MWERKS__)
/* Expand the face-prefix reset, then keep each counter's live range separate. */
#pragma opt_scalarizeliveranges on
#pragma opt_unroll_loops on
#pragma inline_max_size(10000)
#endif
#include "src/collision/CollisionGeometry.h"
#include "src/collision/CollisionTraversal.h"

#define COLLISION_CONTACT_LIMIT 16

#define FACE_PREFIX_FLOOR 0
#define FACE_PREFIX_WALL 1
#define FACE_PREFIX_CEILING 2
#define FACE_PREFIX_COUNT 3

/* Layout views of the fields used here; their ends are not allocation sizes. */

typedef CollisionBounds CollBox;
typedef CollisionShape CollShape;
typedef SweptCollisionShape CollSweep;

typedef struct CollFace {
    fx32 minX;
    fx32 minZ;
    fx32 maxX;
    fx32 maxZ;
    u16 flagBits : 15;
    u16 isLast : 1;
} CollFace;

typedef struct CollFace88 {
    CollFace face;
    u8 pad_12[0x88 - 0x14];
} CollFace88;

typedef struct CollFace84 {
    CollFace face;
    u8 pad_12[0x84 - 0x14];
} CollFace84;

typedef struct ContactPlane {
    s32 distance;
    VecFx32 normal;
    s32 time;
    u8 surfaceType;
    u8 pad_15[3];
} ContactPlane;

typedef struct ContactEntry {
    void *target;
    s32 kind;
    u8 surfaceType;
    u8 pad_09[3];
} ContactEntry;

typedef struct ContactList {
    ContactEntry entries[COLLISION_CONTACT_LIMIT];
    VecFx32 normals[COLLISION_CONTACT_LIMIT];
    u8 count;
} ContactList;

struct CollMover;
struct CollTarget;

typedef BOOL (*TargetFilterFn)(struct CollTarget *target, void *userData, void *context, CollSweep *sweep, u8 moving);
typedef void (*TargetContactFn)(struct CollTarget *target, u8 surfaceType, VecFx32 *normal, void *userData, void *context,
                                ContactList *contacts, CollSweep *sweep, BOOL moving);

/* Source span consumed by CopyShapeFromTemplate: shape followed by its offset. */
typedef struct ShapeTemplate {
    CollShape shape;
    VecFx32 delta;
} ShapeTemplate;

typedef struct CollTarget {
    u8 pad_00[4];
    struct CollTarget *next;
    u8 pad_08[5];
    u8 isMoving;
    u16 groupMask;
    u8 pad_10[4];
    u32 ownerId;
    u8 pad_18[0xc];
    ShapeTemplate motion;
    CollBox sweepBox;
    u8 pad_68[8];
    TargetFilterFn filter;
    void *filterContext;
    u8 pad_78[8];
    TargetContactFn onContact;
    void *onContactContext;
} CollTarget;

typedef struct CollNode {
    u16 flags;
    s16 floorIndex;
    s16 wallIndex;
    s16 ceilIndex;
    CollTarget *targets;
    struct CollNode *parent;
    struct CollNode *children[4];
} CollNode;

typedef struct CollModel {
    u8 pad_00[0x9c];
    CollNode *root;
    CollFace88 *floorFaces;
    CollFace84 *wallFaces;
    CollFace84 *ceilFaces;
} CollModel;

typedef struct FaceQuery {
    void *face;
    s32 kind;
} FaceQuery;

typedef BOOL (*FaceFilterFn)(FaceQuery *query, void *context, CollSweep *sweep, u8 moving);
typedef void (*ContactFn)(ContactEntry *entry, VecFx32 *normal, void *context, ContactList *contacts, CollSweep *sweep,
                          BOOL moving);

typedef struct CollMover {
    u32 flags;
    CollFace88 *floorFaces;
    CollFace84 *wallFaces;
    CollFace84 *ceilFaces;
    u8 pad_10[0x6c];
    u8 hasSweep;
    u8 targetsInPlace;
    u8 pad_7e[0xe];
    u32 ownerId;
    u16 groupMask;
    u8 pad_92;
    u8 kindMask;
    void *userData;
    FaceFilterFn faceFilter;
    void *faceFilterContext;
    CollBox *listBounds;
    CollFace **floorList;
    CollFace **wallList;
    CollFace **ceilList;
    CollSweep *sweep;
    ContactList *contacts;
    u8 planeMode;
    u8 firstContact;
    u8 pad_ba[0xa];
    ContactFn onContact;
    void *onContactContext;
    VecFx32 extent;
    u8 pad_d8[0x2c];
    fx32 maxDistance;
    s32 floorListCount;
    s32 wallListCount;
    s32 ceilListCount;
} CollMover;

typedef BOOL (*ShapeTestFn)(CollSweep *sweep, CollShape *other, ContactPlane *plane, u32 flags);
typedef BOOL (*ShapeSweepFn)(CollSweep *sweep, CollShape *other, ContactPlane *plane, u32 flags, VecFx32 *delta);

extern const ShapeTestFn gCollisionTestDispatch[][6];
extern const ShapeSweepFn gCollisionSweepDispatch[][6];
extern const VecFx32 gZeroVecFx32;
extern VecFx32 data_027e0160;

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag(const VecFx32 *v);
extern fx32 VEC_NormalizeLength(const VecFx32 *v, VecFx32 *out);
extern void ScaleVecFx32InPlace(VecFx32 *v, fx32 scale);
extern void NegateVecFx32(VecFx32 *v);
extern BOOL OverlapsHeightRange(CollFace *face, CollBox *box);
extern BOOL TestMoverAgainstFaceFiltered(CollFace *face, CollMover *mover, ContactPlane *plane, CollBox *box, BOOL moving,
                                         s32 kind, CollFace **excluded, u32 excludedCount);
extern BOOL RecordHitContact(void *target, ContactEntry *entry, ContactEntry *entries, CollMover *mover,
                             ContactPlane *planes, u8 *planeIndex, CollBox *box, BOOL *moving, s32 kind,
                             CollFace **hitFaces, u32 excludedCount, u8 *hitCount, const VecFx32 *start);
extern s32 RecordContactPlane(CollMover *mover, s32 index, ContactPlane *planes, ContactEntry *entries,
                              ContactEntry *entry, BOOL *moving);
extern BOOL ResolvePlaneContacts(CollMover *mover, u8 planeCount, s32 previousCount, ContactPlane *planes,
                                 ContactEntry *entries, VecFx32 velocity, BOOL *moving);
extern void CopyShapeFromTemplate(const ShapeTemplate *src, CollShape *dst, void *buffer);
extern void ResetCollTraversal(CollModel *model);
extern void SetShapePosition(CollShape *shape, VecFx32 *position);

static inline BOOL IsZeroVec(const VecFx32 *v)
{
    return v->x == 0 && v->y == 0 && v->z == 0;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    VEC_Add(a, b, &sum);
    return sum;
}

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 difference;
    VEC_Subtract(a, b, &difference);
    return difference;
}

static inline BOOL BoxesOverlap(const CollBox *a, const CollBox *b)
{
    return a->max.x >= b->min.x && a->min.x <= b->max.x && a->max.z >= b->min.z && a->min.z <= b->max.z && a->max.y >= b->min.y &&
           a->min.y <= b->max.y;
}

static inline BOOL TestFace(CollFace *face, CollMover *mover, ContactPlane *plane, CollBox *box, BOOL moving, s32 kind,
                            CollFace **excluded, u32 excludedCount)
{
    if (box->max.x < face->minX || box->min.x > face->maxX || box->max.z < face->minZ || box->min.z > face->maxZ) {
        return FALSE;
    }
    if (!OverlapsHeightRange(face, box)) {
        return FALSE;
    }
    return TestMoverAgainstFaceFiltered(face, mover, plane, box, moving, kind, excluded, excludedCount);
}

static inline BOOL HitFace(CollFace *face, CollMover *mover, ContactPlane *plane, CollBox *box, BOOL moving, s32 kind,
                           CollFace **hitFaces, u32 excludedCount, ContactEntry *entry, ContactEntry *entries,
                           ContactPlane *planes, u8 *planeIndex, BOOL *movingFlag, u8 *hitCount, const VecFx32 *start)
{
    if (!TestFace(face, mover, plane, box, moving, kind, hitFaces, excludedCount)) {
        return FALSE;
    }
    return RecordHitContact(face, entry, entries, mover, planes, planeIndex, box, movingFlag, kind, hitFaces,
                            excludedCount, hitCount, start);
}

static inline BOOL SweepShapes(CollSweep *sweep, CollShape *other, ContactPlane *plane, u32 flags, VecFx32 *delta)
{
    return gCollisionSweepDispatch[sweep->shape.kind][other->kind](sweep, other, plane, flags, delta);
}

/* Query a resting target using the mover's own displacement. */
static inline BOOL TestMovingShapes(CollSweep *sweep, CollShape *other, ContactPlane *plane, s32 state, u32 flags)
{
    if (state == 2) {
        return gCollisionTestDispatch[sweep->shape.kind][other->kind](sweep, other, plane, flags + 2);
    }
    return SweepShapes(sweep, other, plane, flags, &sweep->delta);
}

/* Moving targets use relative displacement when both objects participate. */
static inline BOOL TestRelativeShapes(CollSweep *sweep, CollShape *other, ContactPlane *plane, s32 state, BOOL moving, VecFx32 *delta)
{
    if (state == 2) {
        return gCollisionTestDispatch[sweep->shape.kind][other->kind](sweep, other, plane,
            moving ? 0xe : ((other->kind == 2 ? 2 : 0) | 8));
    }
    return SweepShapes(sweep, other, plane, moving ? 0xc : 8, delta);
}

static inline BOOL TestTarget(CollTarget *target, CollMover *mover, ContactPlane *plane, u8 moving,
                              CollTarget **excluded, u32 excludedCount, void *shapeBuffer)
{
    VecFx32 relDelta;
    CollShape shapeCopy;
    const VecFx32 *source;
    FaceQuery query;
    FaceQuery request;
    s32 state;
    VecFx32 reversed;
    VecFx32 difference;

    /* 0: apart, 1: overlapping while moving relative to each other, 2: overlapping at rest */
    if (moving) {
        if (target->isMoving) {
            if (BoxesOverlap(&mover->sweep->sweptBounds, &target->sweepBox)) {
                if (IsZeroVec(&target->motion.delta)) {
                    if (IsZeroVec(&mover->sweep->delta)) {
                        state = 2;
                    } else {
                        /* Moving into a resting target: the relative motion is our own. */
                        source = &mover->sweep->delta;
                        state = 1;
                        goto copyRelativeDelta;
                    }
                } else {
                    VEC_Subtract(&mover->sweep->delta, &target->motion.delta, &difference);
                    relDelta = difference;
                    state = IsZeroVec(&relDelta) ? 2 : 1;
                }
            } else {
                state = 0;
            }
        } else {
            s32 overlap;

            if (BoxesOverlap(&mover->sweep->sweptBounds, &target->motion.shape.bounds)) {
                overlap = IsZeroVec(&mover->sweep->delta) ? 2 : 1;
            } else {
                overlap = 0;
            }
            if (overlap != 0) {
                if (overlap != 2) {
                    relDelta = mover->sweep->delta;
                }
                state = 1;
            } else {
                state = 0;
            }
        }
    } else {
        if (target->isMoving) {
            if (BoxesOverlap(&mover->sweep->shape.bounds, &target->sweepBox)) {
                if (IsZeroVec(&target->motion.delta)) {
                    state = 2;
                } else {
                    reversed = target->motion.delta;
                    NegateVecFx32(&reversed);
                    state = 1;
                    source = &reversed;
                copyRelativeDelta:
                    relDelta = *source;
                }
            } else {
                state = 0;
            }
        } else {
            state = BoxesOverlap(&mover->sweep->shape.bounds, &target->motion.shape.bounds) ? 2 : 0;
        }
    }
    if (state == 0) {
        return FALSE;
    }
    if (target->groupMask & mover->groupMask) {
        return FALSE;
    }
    if (excludedCount != 0) {
        u8 i = 0;
        do {
            if (target == excluded[i]) {
                return FALSE;
            }
            i++;
        } while (i < excludedCount);
    }
    if (target->filter != NULL && !target->filter(target, mover->userData, target->filterContext, mover->sweep, moving)) {
        return FALSE;
    }
    if (mover->faceFilter != NULL) {
        request.face = target;
        request.kind = 4;
        query = request;
        if (!mover->faceFilter(&query, mover->faceFilterContext, mover->sweep, moving)) {
            return FALSE;
        }
    }
    if (target->isMoving) {
        if (!mover->targetsInPlace) {
            CopyShapeFromTemplate(&target->motion, &shapeCopy, shapeBuffer);
            if (moving) {
                return TestMovingShapes(mover->sweep, &shapeCopy, plane, state, 4);
            } else {
                return gCollisionTestDispatch[mover->sweep->shape.kind][shapeCopy.kind](mover->sweep, &shapeCopy, plane, 0);
            }
        } else if (moving) {
            return TestRelativeShapes(mover->sweep, &target->motion.shape, plane, state, TRUE, &relDelta);
        } else {
            return TestRelativeShapes(mover->sweep, &target->motion.shape, plane, state, FALSE, &relDelta);
        }
    } else if (mover->hasSweep) {
        return TestMovingShapes(mover->sweep, &target->motion.shape, plane, state, 4);
    } else {
        return gCollisionTestDispatch[mover->sweep->shape.kind][target->motion.shape.kind](mover->sweep, &target->motion.shape, plane, 0);
    }
}

static inline BOOL StopSweepAt(CollMover *mover, const VecFx32 *start)
{
    mover->sweep->delta = gZeroVecFx32;
    *(VecFx32 *)mover->sweep->shape.geometry = *start;
    return TRUE;
}

static inline VecFx32 GetSweepVelocity(CollMover *mover)
{
    if (mover->hasSweep) {
        return mover->sweep->delta;
    }
    if (mover->sweep->shape.kind != 2) {
        return gZeroVecFx32;
    }
    {
        VecFx32 velocity;
        VEC_Subtract((VecFx32 *)mover->sweep->shape.geometry + 1, mover->sweep->shape.geometry, &velocity);
        return velocity;
    }
}

static inline void ApplySweepDelta(CollSweep *sweep)
{
    VecFx32 position;
    VecFx32 sum;

    VEC_Add(sweep->shape.geometry, &sweep->delta, &sum);
    position = sum;

    SetShapePosition(&sweep->shape, &position);
    OffsetBoxByDelta(&sweep->shape.bounds, &sweep->sweptBounds, &sweep->delta);
}

void ResolveCollisionTreeContacts(CollNode *node, CollMover *mover, CollModel *model)
{
    ContactPlane planeBuffer[COLLISION_CONTACT_LIMIT];
    ContactEntry entries[COLLISION_CONTACT_LIMIT];
    u8 shapeBuffer[0xd0];
    ContactEntry entry;
    VecFx32 start;
    CollFace *floorHitFaces[COLLISION_CONTACT_LIMIT];
    CollFace *wallHitFaces[COLLISION_CONTACT_LIMIT];
    CollFace *ceilHitFaces[COLLISION_CONTACT_LIMIT];
    CollTarget *hitTargets[COLLISION_CONTACT_LIMIT];
    VecFx32 velocity;
    CollBox *box;
    ContactPlane *planes;
    u8 processedPrefixes[FACE_PREFIX_COUNT];
    u8 previousPlaneCount;
    u8 planeIndex;
    u8 iteration;
    u8 floorHits;
    u8 wallHits;
    u8 ceilHits;
    u8 targetExcluded;
    u8 targetHits;
    BOOL moving;
    BOOL hasPlanes;
    BOOL hasTargets;
    u32 useFloor;
    u32 useWall;
    u32 useCeil;
    u32 useTargets;
    s32 floorCount;
    s32 wallCount;
    s32 ceilCount;
    u32 ownerId;
    u32 mask0;
    u32 mask1;
    u32 mask2;
    u32 mask3;
    s32 i;
    CollFace *face;
    CollTarget *target;
    s32 quarter;
    CollTraversalFrame *frame;
    u32 nodeFlags;
    s32 descentChild;
    CollTraversalFrame *parentFrame;
    CollTraversalFrame *nextFrame;
    u16 siblingFlags;
    s32 siblingChild;
    s32 centerX;
    s16 previousChild;

    box = mover->hasSweep ? &mover->sweep->sweptBounds : &mover->sweep->shape.bounds;
    if (mover->planeMode != 2) {
        planes = planeBuffer;
    } else {
        planes = NULL;
    }
    previousPlaneCount = 0;
    planeIndex = 0;
    start = *(VecFx32 *)mover->sweep->shape.geometry;
    iteration = 0;
    floorHits = 0;
    wallHits = 0;
    ceilHits = 0;
    /* hasSweep selects swept bounds; moving may be cleared by contact resolution. */
    moving = mover->hasSweep;
    /* Prefix lengths exclude contacts already processed; hit counts may grow during a pass. */
    {
        u32 category;
        for (category = 0; category < FACE_PREFIX_COUNT; category++) {
            processedPrefixes[category] = 0;
        }
    }
    targetHits = targetExcluded = 0;
    if (moving && IsZeroVec(&mover->sweep->delta)) {
        moving = FALSE;
    }
    hasPlanes = planes != NULL;

    for (;;) {
        u8 kindMask = mover->kindMask;

        useFloor = kindMask & 1;
        useWall = kindMask & 2;
        useCeil = kindMask & 4;
        useTargets = kindMask & 8;

        if (useFloor != 0 && (floorCount = mover->floorListCount) >= 0) {
            entry.kind = 1;
            for (i = 0; i < floorCount; i++) {
                face = mover->floorList[i];
                if (HitFace(face, mover, planes != NULL ? &planes[planeIndex] : NULL, box, moving, 1, floorHitFaces, processedPrefixes[FACE_PREFIX_FLOOR], &entry, entries, planes, &planeIndex, &moving,
                            &floorHits, &start)) {
                    goto done;
                }
            }
            processedPrefixes[FACE_PREFIX_FLOOR] = floorHits;
            useFloor = 0;
        }
        if (useWall != 0 && (wallCount = mover->wallListCount) >= 0) {
            entry.kind = 2;
            for (i = 0; i < wallCount; i++) {
                face = mover->wallList[i];
                if (HitFace(face, mover, planes != NULL ? &planes[planeIndex] : NULL, box, moving, 2, wallHitFaces, processedPrefixes[FACE_PREFIX_WALL], &entry, entries, planes, &planeIndex, &moving,
                            &wallHits, &start)) {
                    goto done;
                }
            }
            processedPrefixes[FACE_PREFIX_WALL] = wallHits;
            useWall = 0;
        }
        if (useCeil != 0 && (ceilCount = mover->ceilListCount) >= 0) {
            entry.kind = 3;
            for (i = 0; i < ceilCount; i++) {
                face = mover->ceilList[i];
                if (HitFace(face, mover, planes != NULL ? &planes[planeIndex] : NULL, box, moving, 3, ceilHitFaces, processedPrefixes[FACE_PREFIX_CEILING], &entry, entries, planes, &planeIndex, &moving,
                            &ceilHits, &start)) {
                    goto done;
                }
            }
            processedPrefixes[FACE_PREFIX_CEILING] = ceilHits;
            useCeil = 0;
        }

        if (useFloor != 0) {
            mask0 = 1;
            mask1 = 2;
            mask2 = 4;
            mask3 = 8;
        } else {
            mask0 = 0;
            mask1 = 0;
            mask2 = 0;
            mask3 = 0;
        }
        if (useWall != 0) {
            mask0 |= 0x10;
            mask1 |= 0x20;
            mask2 |= 0x40;
            mask3 |= 0x80;
        }
        if (useCeil != 0) {
            mask0 |= 0x100;
            mask1 |= 0x200;
            mask2 |= 0x400;
            mask3 |= 0x800;
        }
        if (useTargets != 0) {
            mask0 |= 0x1000;
            mask1 |= 0x2000;
            mask2 |= 0x4000;
            mask3 |= 0x8000;
        }
        hasTargets = useTargets != 0;

    restart:
        if (hasTargets) {
            ownerId = mover->ownerId;
            entry.kind = 4;
            for (entry.target = node->targets; entry.target != NULL; entry.target = ((CollTarget *)entry.target)->next) {
                target = entry.target;
                if (target->ownerId != ownerId &&
                    TestTarget(target, mover, planes != NULL ? &planes[planeIndex] : NULL, moving, hitTargets,
                               targetExcluded, shapeBuffer)) {
                    if (targetHits == COLLISION_CONTACT_LIMIT) {
                        StopSweepAt(mover, &start);
                        goto done;
                    }
                    hitTargets[targetHits++] = entry.target;
                    if (planes != NULL) {
                        if (!moving && mover->sweep->shape.kind != 2) {
                            planes[planeIndex].time = -1;
                        }
                        entry.surfaceType = planes[planeIndex].surfaceType;
                    }
                    switch (RecordContactPlane(mover, planeIndex, planes, entries, &entry, &moving)) {
                    case 0:
                        break;
                    case 1:
                        if (++planeIndex == COLLISION_CONTACT_LIMIT) {
                            StopSweepAt(mover, &start);
                            goto done;
                        }
                        break;
                    case 2:
                        goto done;
                    }
                }
            }
            targetExcluded = targetHits;
        }
        if (useFloor != 0 && node->floorIndex >= 0) {
            entry.kind = 1;
            for (entry.target = &mover->floorFaces[node->floorIndex];; entry.target = (CollFace88 *)entry.target + 1) {
                if (HitFace(entry.target, mover, hasPlanes ? &planes[planeIndex] : NULL, box, moving, 1, floorHitFaces, processedPrefixes[FACE_PREFIX_FLOOR], &entry, entries, planes, &planeIndex, &moving,
                            &floorHits, &start)) {
                    goto done;
                }
                if (((CollFace *)entry.target)->isLast) {
                    break;
                }
            }
            processedPrefixes[FACE_PREFIX_FLOOR] = floorHits;
        }
        if (useWall != 0 && node->wallIndex >= 0) {
            entry.kind = 2;
            for (entry.target = &mover->wallFaces[node->wallIndex];; entry.target = (CollFace84 *)entry.target + 1) {
                if (HitFace(entry.target, mover, hasPlanes ? &planes[planeIndex] : NULL, box, moving, 2, wallHitFaces, processedPrefixes[FACE_PREFIX_WALL], &entry, entries, planes, &planeIndex, &moving,
                            &wallHits, &start)) {
                    goto done;
                }
                if (((CollFace *)entry.target)->isLast) {
                    break;
                }
            }
            processedPrefixes[FACE_PREFIX_WALL] = wallHits;
        }
        if (useCeil != 0 && node->ceilIndex >= 0) {
            entry.kind = 3;
            for (entry.target = &mover->ceilFaces[node->ceilIndex];; entry.target = (CollFace84 *)entry.target + 1) {
                if (HitFace(entry.target, mover, hasPlanes ? &planes[planeIndex] : NULL, box, moving, 3, ceilHitFaces, processedPrefixes[FACE_PREFIX_CEILING], &entry, entries, planes, &planeIndex, &moving,
                            &ceilHits, &start)) {
                    goto done;
                }
                if (((CollFace *)entry.target)->isLast) {
                    break;
                }
            }
            processedPrefixes[FACE_PREFIX_CEILING] = ceilHits;
        }

        frame = gCollisionTraversalTop;
        nodeFlags = node->flags;
        if (nodeFlags != 0) {
            nextFrame = frame + 1;
            quarter = frame->region.size / 4;
            centerX = frame->region.centerX;
            if (box->max.x < centerX) {
                nodeFlags &= 0x5555;
            } else if (box->min.x > centerX) {
                nodeFlags &= 0xaaaa;
            }
            if (box->max.z < frame->region.centerZ) {
                nodeFlags &= 0x3333;
            } else if (box->min.z > frame->region.centerZ) {
                nodeFlags &= 0xcccc;
            }

            descentChild = 0xf;
            if (nodeFlags & mask0) {
                nextFrame->region.centerX = centerX - quarter;
                nextFrame->region.centerZ = frame->region.centerZ - quarter;
                descentChild = 0;
            } else if (nodeFlags & mask1) {
                nextFrame->region.centerX = centerX + quarter;
                nextFrame->region.centerZ = frame->region.centerZ - quarter;
                descentChild = 1;
            } else if (nodeFlags & mask2) {
                nextFrame->region.centerX = centerX - quarter;
                nextFrame->region.centerZ = frame->region.centerZ + quarter;
                descentChild = 2;
            } else if (nodeFlags & mask3) {
                nextFrame->region.centerX = centerX + quarter;
                nextFrame->region.centerZ = frame->region.centerZ + quarter;
                descentChild = 3;
            }

            if (descentChild != 0xf) {
                node = node->children[descentChild];
                nextFrame->childIndex = descentChild;
                frame->nodeFlags = nodeFlags;
                gCollisionTraversalTop = nextFrame;
                goto restart;
            }
        }

        while (frame != gCollisionTraversalFrames) {
            previousChild = frame->childIndex;
            if (previousChild == 3) {
                frame--;
                node = node->parent;
                continue;
            }

            parentFrame = frame - 1;
            node = node->parent;
            siblingFlags = parentFrame->nodeFlags;
            quarter = parentFrame->region.size / 4;
            siblingChild = 0;

            switch (previousChild) {
            case 0:
                if (siblingFlags & mask1) {
                    frame->region.centerX = parentFrame->region.centerX + quarter;
                    siblingChild = 1;
                    frame->region.centerZ = parentFrame->region.centerZ - quarter;
                    break;
                }
            case 1:
                if (siblingFlags & mask2) {
                    frame->region.centerX = parentFrame->region.centerX - quarter;
                    siblingChild = 2;
                    frame->region.centerZ = parentFrame->region.centerZ + quarter;
                    break;
                }
            case 2:
                if (siblingFlags & mask3) {
                    frame->region.centerX = parentFrame->region.centerX + quarter;
                    siblingChild = 3;
                    frame->region.centerZ = parentFrame->region.centerZ + quarter;
                }
                break;
            }

            if (siblingChild != 0) {
                node = node->children[siblingChild];
                frame->childIndex = siblingChild;
                gCollisionTraversalTop = frame;
                goto restart;
            }
            frame--;
        }

        if (planeIndex == 0 || mover->planeMode != 0) {
            goto done;
        }
        if (!ResolvePlaneContacts(mover, planeIndex, previousPlaneCount, planes, entries, (velocity = GetSweepVelocity(mover)), &moving)) {
            goto done;
        }
        /* Ten retries are allowed after the initial traversal. */
        if (iteration >= 10) {
            break;
        }
        iteration++;
        /* Restore the processed prefixes before searching again with the revised motion. */
        floorHits = processedPrefixes[FACE_PREFIX_FLOOR];
        wallHits = processedPrefixes[FACE_PREFIX_WALL];
        ceilHits = processedPrefixes[FACE_PREFIX_CEILING];
        previousPlaneCount = planeIndex;
        node = model->root;
        mover->floorFaces = model->floorFaces;
        mover->wallFaces = model->wallFaces;
        mover->ceilFaces = model->ceilFaces;
        targetHits = targetExcluded;
        ResetCollTraversal(model);
        if (mover->listBounds != NULL) {
            CollBox *bounds = mover->listBounds;
            CollBox *shapeBox = &mover->sweep->shape.bounds;

            if (shapeBox->max.x > bounds->max.x || shapeBox->min.x < bounds->min.x || shapeBox->max.y > bounds->max.y ||
                shapeBox->min.y < bounds->min.y || shapeBox->max.z > bounds->max.z || shapeBox->min.z < bounds->min.z) {
                mover->floorListCount = -1;
                mover->wallListCount = -1;
                mover->ceilListCount = -1;
            }
        }
    }
    mover->sweep->delta = gZeroVecFx32;

done:
    {
        VecFx32 *normals;
        u8 index;
        u8 contactCount;
        ContactList *contacts;

        contacts = mover->contacts;
        normals = contacts->normals;
        contactCount = contacts->count;
        index = mover->firstContact;

        if (mover->onContact != NULL) {
            for (; index < contactCount; index++) {
                ContactEntry *contact = &contacts->entries[index];

                if (contact->kind != 0) {
                    if (contact->kind == 4) {
                        CollTarget *hit = contact->target;

                        if (hit->onContact != NULL) {
                            hit->onContact(hit, contact->surfaceType, &normals[index], mover->userData,
                                           hit->onContactContext, mover->contacts, mover->sweep, moving);
                        }
                    }
                    mover->onContact(contact, &normals[index], mover->onContactContext, mover->contacts,
                                     mover->sweep, moving);
                }
            }
        } else {
            for (; index < contactCount; index++) {
                ContactEntry *contact = &contacts->entries[index];

                if (contact->kind != 0) {
                    if (contact->kind == 4) {
                        CollTarget *hit = contact->target;

                        if (hit->onContact != NULL) {
                            hit->onContact(hit, contact->surfaceType, &normals[index], mover->userData,
                                           hit->onContactContext, mover->contacts, mover->sweep, moving);
                        }
                    }
                }
            }
        }
    }
    if (mover->hasSweep) {
        ApplySweepDelta(mover->sweep);
    }
    if (mover->planeMode != 0) {
        return;
    }
    data_027e0160 = SubtractVec(mover->sweep->shape.geometry, &start);
    if (mover->maxDistance == 0x7fffffff) {
        return;
    }
    {
        fx32 extra = (mover->hasSweep || mover->sweep->shape.kind == 2) ? VEC_Mag(&mover->extent) : 0;
        fx32 limit = mover->maxDistance + extra;

        if (VEC_Mag(&data_027e0160) > limit) {
            fx32 maxDistance = mover->maxDistance;
            VecFx32 position;

            VEC_NormalizeLength(&data_027e0160, &data_027e0160);
            ScaleVecFx32InPlace(&data_027e0160, maxDistance);
            position = AddVec(&start, &data_027e0160);
            SetShapePosition(&mover->sweep->shape, &position);
        }
    }
}
