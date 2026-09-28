#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollBox {
    fx32 maxX;
    fx32 maxY;
    fx32 maxZ;
    fx32 minX;
    fx32 minY;
    fx32 minZ;
} CollBox;

typedef struct CollSegment {
    VecFx32 start;
    VecFx32 end;
    VecFx32 direction;
    fx32 length;
} CollSegment;

typedef struct CollShape {
    CollSegment *segment;
    CollBox box;
    s32 kind;
} CollShape;

typedef struct CollSweep {
    CollShape shape;
    VecFx32 delta;
    CollBox sweepBox;
} CollSweep;

typedef struct ContactPlane {
    s32 distance;
    VecFx32 normal;
    s32 time;
    u8 surfaceType;
    u8 pad_15[3];
} ContactPlane;

typedef struct ContactEntry {
    s32 value;
    s32 field;
    s32 unk_08;
} ContactEntry;

typedef struct ContactSlot {
    s32 value;
    s32 field;
    u8 surfaceType;
    u8 pad_09[3];
} ContactSlot;

typedef struct ContactList {
    ContactSlot slots[16];
    VecFx32 normals[16];
    u8 count;
} ContactList;

typedef struct Mover {
    u8 pad_00[0x7c];
    u8 hasSweep;
    u8 pad_7d[0x33];
    CollSweep *sweep;
    ContactList *contacts;
    u8 recordsContacts;
    u8 replaceSlot;
} Mover;

typedef struct MotionQueue {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0c;
    s32 unk_10;
} MotionQueue;

typedef void (*ShapeBoundsFn)(CollShape *shape, CollBox *box);

extern ShapeBoundsFn g_shapeBoundsTable_020559c0[];
extern ContactPlane g_lastContactPlane_027e0148;
extern MotionQueue g_motionQueue_027e0134;

extern s32 func_02031bf0(Mover *mover, ContactEntry *entry, s32 index, BOOL *moving, ContactPlane *planes, ContactEntry *entries);
extern void func_02032008(ContactList *list, s32 value, s32 field, u8 surfaceType, VecFx32 *normal);
extern void SetMotionQueueField_02031b88(ContactEntry *entry);
extern void OffsetBoxByDelta_0203ac70(const CollBox *src, CollBox *dst, const VecFx32 *delta);
extern void func_0203b1f0(CollSegment *segment);
extern void func_0203b4ac(VecFx32 *out, ContactPlane *plane, CollSegment *segment);
extern void ScaleVecHighShift_0204a640(VecFx32 *vec, s32 scale);

s32 RecordContactPlane_02031d24(Mover *mover, s32 index, ContactPlane *planes, ContactEntry *entries, ContactEntry *entry, BOOL *moving)
{
    BOOL stopped = FALSE;
    BOOL recorded;
    s32 result;

    result = func_02031bf0(mover, entry, index, moving, planes, entries);
    if (result != 1) {
        return result;
    }
    if (planes == NULL) {
        mover->contacts->slots[mover->contacts->count].value = entry->value;
        mover->contacts->slots[mover->contacts->count].field = entry->field;
        mover->contacts->count++;
        return 2;
    }
    if (!mover->recordsContacts) {
        recorded = FALSE;
    } else {
        if (mover->hasSweep) {
            if (*moving) {
                VecFx32 delta;
                CollSweep *sweep;
                fx32 time = planes[index].time;

                delta = mover->sweep->delta;
                ScaleVecHighShift_0204a640(&delta, time);
                sweep = mover->sweep;
                sweep->delta = delta;
                OffsetBoxByDelta_0203ac70(&sweep->shape.box, &sweep->sweepBox, &sweep->delta);
                if (mover->sweep->delta.x == 0 && mover->sweep->delta.y == 0 && mover->sweep->delta.z == 0) {
                    stopped = TRUE;
                }
            } else {
                stopped = TRUE;
            }
        } else {
            VecFx32 end;
            CollSweep *sweep;

            func_0203b4ac(&end, &planes[index], mover->sweep->shape.segment);
            mover->sweep->shape.segment->end = end;
            func_0203b1f0(mover->sweep->shape.segment);
            sweep = mover->sweep;
            g_shapeBoundsTable_020559c0[sweep->shape.kind](&sweep->shape, &sweep->shape.box);
            if (mover->sweep->shape.segment->length == 0) {
                stopped = TRUE;
            }
        }
        g_lastContactPlane_027e0148 = planes[index];
        recorded = TRUE;
    }
    if (recorded) {
        if (mover->contacts->count == mover->replaceSlot) {
            func_02032008(mover->contacts, entry->value, entry->field, planes[index].surfaceType, &planes[index].normal);
        } else {
            mover->contacts->slots[mover->replaceSlot].value = entry->value;
            mover->contacts->slots[mover->replaceSlot].field = entry->field;
            mover->contacts->slots[mover->replaceSlot].surfaceType = planes[index].surfaceType;
            mover->contacts->normals[mover->replaceSlot] = planes[index].normal;
            g_motionQueue_027e0134.unk_04 = 0;
            g_motionQueue_027e0134.unk_08 = 0;
            g_motionQueue_027e0134.unk_0c = 0;
            g_motionQueue_027e0134.unk_10 = 0;
        }
        SetMotionQueueField_02031b88(entry);
        if (stopped) {
            return 2;
        }
        return 0;
    }
    if (!mover->recordsContacts) {
        entries[index] = *entry;
        return 1;
    }
    return stopped ? 2 : 1;
}
