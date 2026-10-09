#pragma opt_propagation off
#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ContactPlane {
    s32 distance;
    VecFx32 normal;
    s32 priority;
    u8 surfaceType;
    u8 pad_15[3];
} ContactPlane;

typedef struct ContactEntry {
    s32 value;
    s32 field;
    s32 unk_08;
} ContactEntry;

typedef struct ContactList {
    u8 pad_00[0xc0];
    VecFx32 normals[16];
    u8 count;
    u8 ids[32];
    u8 idCount;
} ContactList;

typedef struct Mover {
    u8 pad_00[0x7c];
    u8 tracksMotion;
    u8 pad_7d[0x33];
    void *world;
    ContactList *contacts;
    u8 pad_b8[0x14];
    VecFx32 sweepMotion;
    VecFx32 direction;
    s8 contactPlane[16];
    s8 planeContact[16];
} Mover;

extern fx32 FX_Div(fx32 numer, fx32 denom);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ApplyShapeVelocity(Mover *mover, VecFx32 *velocity);
extern BOOL TestShapeAgainstSurface(void *world, ContactEntry *entry, ContactPlane *plane);
extern BOOL TestSweepAgainstSurface(void *world, ContactEntry *entry, ContactPlane *plane);
extern void SetMotionQueueField(ContactEntry *entry);
extern s32 DispatchContactCallbacks(Mover *mover, ContactEntry *entry, s32 index, BOOL *moving, ContactPlane *planes, ContactEntry *entries);
extern void PushContact(ContactList *list, s32 value, s32 field, u8 surfaceType, VecFx32 *normal);
extern void RemoveContactSlot(Mover *mover, ContactList *list, u8 slot, u8 planeCount);
extern BOOL HasVelocityDeviated(VecFx32 *velocity, VecFx32 *original);
extern void AddUniqueContactId(ContactList *list, u8 id);
extern VecFx32 ResolveSlideMovement(ContactPlane *plane, VecFx32 *normals, u8 normalCount, s32 *hitCount, u8 *hitIds, u8 *hitSlots, VecFx32 *extra, ContactPlane *planes, u8 planeCount);

static inline fx32 SafeTime(fx32 numer, fx32 denom)
{
    s32 numerSign;
    s32 denomSign;
    if (denom != 0) {
        return FX_Div(numer, denom);
    }
    if (numer == 0) {
        numerSign = 0;
    } else if (numer > 0) {
        numerSign = 1;
    } else {
        numerSign = -1;
    }
    if (denom >= 0) {
        denomSign = 1;
    } else {
        denomSign = -1;
    }
    return denomSign * (numerSign * 0x7fffffff);
}

BOOL ResolvePlaneContacts(Mover *mover, u8 planeCount, s32 reserved, ContactPlane *planes, ContactEntry *entries, VecFx32 velocity, BOOL *moving)
{
    VecFx32 original;
    u8 hitIds[16];
    u8 hitSlots[16];
    VecFx32 push;
    VecFx32 haltVelocity;
    VecFx32 resetVelocity;
    s32 hitCount;
    u8 iter;
    u8 maxIter;
    BOOL result;
    u8 idCount;
    u8 best;
    u8 i;
    u8 j;
    s32 minPriority;
    s32 bestTime;
    BOOL better;
    ContactPlane *plane;
    ContactEntry *entryTable = entries;
    ContactPlane *planeTable = planes;
    ContactPlane *candidates = planes;

    result = FALSE;
    maxIter = planeCount * 2;
    original = velocity;
    for (iter = 0; !result && iter < maxIter; iter++) {
        minPriority = 0x7fffffff;
        for (i = 0, best = 0xff; i < planeCount; i++) {
            plane = &planes[i];
            if (candidates[i].distance >= 0 && mover->planeContact[i] == -1) {
                better = FALSE;
                if (minPriority >= 0 && minPriority > plane->priority) {
                    if (plane->priority <= 0) {
                        if (*moving) {
                            bestTime = SafeTime(plane->distance, VEC_DotProduct(&plane->normal, &mover->direction));
                        } else {
                            bestTime = plane->distance;
                        }
                    }
                    better = TRUE;
                }
                if (plane->priority <= 0 && minPriority == plane->priority) {
                    s32 time;
                    if (*moving) {
                        time = SafeTime(plane->distance, VEC_DotProduct(&planeTable[i].normal, &mover->direction));
                    } else {
                        time = plane->distance;
                    }
                    if (bestTime < time) {
                        bestTime = time;
                        better = TRUE;
                    }
                }
                if (better) {
                    minPriority = plane->priority;
                    best = i;
                }
            }
        }
        if (best == 0xff) {
            break;
        }
        plane = &planes[best];
        if (planes[best].distance > 0) {
            u8 normalCount;
            hitCount = 0;
            normalCount = mover->contacts->count;
            for (i = 0; i < normalCount; i++) {
                if (i != mover->planeContact[best] && VEC_DotProduct(&mover->contacts->normals[i], &plane->normal) > 0xff0) {
                    RemoveContactSlot(mover, mover->contacts, i, planeCount);
                    break;
                }
            }
            push = ResolveSlideMovement(&planeTable[best], mover->contacts->normals, mover->contacts->count, &hitCount, hitIds, hitSlots, &mover->sweepMotion, planes, planeCount);
            if (hitCount == 3) {
                i = 0;
                if (hitSlots[0] != 0xff) {
                    do {
                        s8 planeIndex = mover->contactPlane[hitSlots[i]];
                        if (planeIndex != -1 && i != mover->planeContact[best]) {
                            int k;
                            planes[planeIndex].distance = 0x80000000;
                            RemoveContactSlot(mover, mover->contacts, hitSlots[i], planeCount);
                            for (k = i + 1; hitSlots[k] != 0xff; k++) {
                                if (hitSlots[k] > hitSlots[i]) {
                                    hitSlots[k]--;
                                }
                            }
                        }
                        i++;
                    } while (hitSlots[i] != 0xff);
                }
            } else if (hitCount >= 4) {
                idCount = (hitCount != 7 ? (u8)(hitCount - 4) : 0) + 1;
                if (mover->contacts->idCount < 0x20) {
                    AddUniqueContactId(mover->contacts, mover->contacts->count);
                    for (j = 0; j < idCount; j++) {
                        if (mover->contacts->idCount == 0x20) {
                            break;
                        }
                        AddUniqueContactId(mover->contacts, hitIds[j]);
                    }
                }
                if (mover->contacts->idCount >= 4) {
                    VecFx32 zero;
                    u8 index;
                    zero.x = 0;
                    zero.y = 0;
                    zero.z = 0;
                    haltVelocity = zero;
                    ApplyShapeVelocity(mover, &haltVelocity);
                    index = best;
                    PushContact(mover->contacts, entries[index].value, entries[index].field, planes[index].surfaceType, &plane->normal);
                    SetMotionQueueField(&entries[index]);
                    return FALSE;
                }
            }
            if (push.x != 0 || push.y != 0 || push.z != 0) {
                VecFx32 sum;
                VEC_Add(&velocity, &push, &sum);
                velocity = sum;
                if (mover->tracksMotion) {
                    *moving = (velocity.x != 0 || velocity.y != 0 || velocity.z != 0);
                }
                ApplyShapeVelocity(mover, &velocity);
                for (i = 0; i < planeCount; i++) {
                    if (planes[i].distance != (s32)0x80000000) {
                        if (i == best) {
                            planes[i].distance = 0;
                        } else {
                            BOOL kept;
                            if (*moving) {
                                kept = TestSweepAgainstSurface(mover->world, &entries[i], &planes[i]);
                            } else {
                                kept = TestShapeAgainstSurface(mover->world, &entries[i], &planes[i]);
                            }
                            if (!kept) {
                                planes[i].distance = 0x80000000;
                            } else if (DispatchContactCallbacks(mover, &entryTable[i], i, moving, planes, entries) == 2) {
                                return FALSE;
                            }
                        }
                    }
                }
            }
        } else {
            u8 normalCount;
            BOOL blocked = FALSE;
            normalCount = mover->contacts->count;
            for (j = 0; j < normalCount; j++) {
                if (j != mover->planeContact[best] && VEC_DotProduct(&mover->contacts->normals[j], &plane->normal) > 0xff0) {
                    plane->distance = 0x80000000;
                    blocked = TRUE;
                    break;
                }
            }
            if (blocked) {
                continue;
            }
        }
        mover->contactPlane[mover->contacts->count] = best;
        mover->planeContact[best] = mover->contacts->count;
        PushContact(mover->contacts, entries[best].value, entries[best].field, planes[best].surfaceType, &planes[best].normal);
        SetMotionQueueField(&entries[best]);
        if (!result && HasVelocityDeviated(&velocity, &original)) {
            result = TRUE;
        }
    }
    if (iter == maxIter) {
        VecFx32 zero;
        zero.x = 0;
        zero.y = 0;
        zero.z = 0;
        resetVelocity = zero;
        ApplyShapeVelocity(mover, &resetVelocity);
        return FALSE;
    }
    if (!result && HasVelocityDeviated(&velocity, &original)) {
        result = TRUE;
    }
    ApplyShapeVelocity(mover, &velocity);
    if (result) {
        for (i = 0; i < planeCount; i++) {
            ContactPlane *plane = &planes[i];
            if (plane->distance == (s32)0x80000000 && VEC_DotProduct(&plane->normal, &velocity) < 0) {
                BOOL kept;
                if (*moving) {
                    kept = TestSweepAgainstSurface(mover->world, &entries[i], plane);
                } else {
                    kept = TestShapeAgainstSurface(mover->world, &entries[i], plane);
                }
                if (!kept) {
                    plane->distance = 0x80000000;
                } else if (DispatchContactCallbacks(mover, &entryTable[i], i, moving, planes, entries) == 2) {
                    return FALSE;
                }
            }
        }
    }
    return result;
}
