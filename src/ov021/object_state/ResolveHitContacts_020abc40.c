#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    void *data;
    s32 bounds[6];
    s32 kind;
    u8 pad_20[0x24];
    s16 *hitIds;
} HitRecord;

typedef struct {
    fx32 distance;
    VecFx32 direction;
    s32 pad_10[2];
} HitResult;

typedef struct {
    u16 id;
    u16 isPartner : 1;
    u16 isLocked : 1;
    u16 flagBits : 14;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 extent[4];
} EventTargetInfo;

typedef struct {
    s32 id;
    s32 count;
    s32 param;
    VecFx32 start;
    VecFx32 end;
    u32 result;
} PathSegment;

typedef struct {
    u8 pad_00[0x10];
    u8 passive;
    u8 pad_11[0x13];
    u16 isActive : 1;
    u16 isReactive : 1;
} HitTarget;

typedef struct HitManager {
    u8 pad_00[0xbc];
    VecFx32 origin;
    u8 pad_c8[0x114];
    s32 state;
    u8 pad_1e0[0x4c];
    s32 (*getState)(struct HitManager *manager);

} HitManager;

typedef struct {
    u32 flags;
    u32 pad_04;
    s32 kind;
    VecFx32 point;
    u16 targetId;
    u16 partId;
} HitReport;

extern HitManager *GetBoundedEntryField_0206db5c(int index);
extern s32 func_ov001_0208789c(HitRecord *record, HitResult *result, u16 *partId);
extern BOOL func_ov021_020abfb0(HitRecord *record, HitResult *result);
extern BOOL GetStageEventTargetInfo_02087960(u32 id, EventTargetInfo *out);
extern u32 func_0202a9d0(u32 range);
extern VecFx32 func_ov021_020abebc(HitRecord *record, HitTarget *target, VecFx32 *position);
extern void InitPathSegment_020ac104(PathSegment *segment, s32 id, s32 count, s32 param, const VecFx32 *start, const VecFx32 *end);
extern BOOL func_ov021_020ac33c(HitTarget *target, PathSegment *segment);
extern void AddSessionCounter_02063a80(int index, int amount);
extern BOOL IsObjectIdle_020ac7f0(HitTarget *target);
extern VecFx32 GetShapeCenter_0203b43c(const HitRecord *shape);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

BOOL ResolveHitContacts_020abc40(int owner, HitRecord *record, HitTarget *target, HitReport *report)
{
    HitManager *manager = GetBoundedEntryField_0206db5c(owner);
    BOOL done = FALSE;
    s32 id;
    HitResult result;
    VecFx32 offset;
    VecFx32 centerCopy;
    EventTargetInfo info;
    PathSegment segment;
    VecFx32 end;
    VecFx32 contact;
    VecFx32 center;
    u16 partId;

    do {
        BOOL hit = FALSE;
        int i;
        BOOL seen;
        s16 *ids;

        id = func_ov001_0208789c(record, &result, &partId);
        if (id == 0) {
            break;
        }
        ids = record->hitIds;
        if (ids != NULL) {
            seen = FALSE;

            for (i = 0; i < 8; i++) {
                if (id == ids[i]) {
                    seen = TRUE;
                    break;
                }
            }
            if (seen) {
                continue;
            }
        }
        if (!func_ov021_020abfb0(record, &result)) {
            continue;
        }
        if (!GetStageEventTargetInfo_02087960(id, &info)) {
            continue;
        }
        if (target != NULL && target->passive == 0) {
            s32 state;

            if (manager->getState != NULL) {
                state = manager->getState(manager);
            } else {
                state = manager->state;
            }
            if (state == 7 && !info.isLocked && func_0202a9d0(100) < 75) {
                report->flags |= 0x20;
                hit = TRUE;
            }
        }
        if (info.isLocked && target != NULL && target->isReactive && !target->isActive) {
            ids = record->hitIds;
            if (ids != NULL) {
                for (i = 0; i < 8; i++) {
                    if (ids[i] == -1) {
                        ids[i] = id;
                        break;
                    }
                }
            }
            continue;
        }
        if (target != NULL && !hit) {

            contact = func_ov021_020abebc(record, target, &info.position);
            end = contact;
            InitPathSegment_020ac104(&segment, id, partId, owner, &manager->origin, &end);
            if (func_ov021_020ac33c(target, &segment)) {
                report->flags |= 4;
                AddSessionCounter_02063a80(8, 1);
            }
            if (segment.result != 0x80000000) {
                done = TRUE;
                if (segment.result & 1) {
                    if (IsObjectIdle_020ac7f0(target)) {
                        report->flags |= 1;
                    } else {
                        report->flags |= 0x10;
                    }
                } else if (target->isActive) {
                    report->flags |= 2;
                }
                if (info.isLocked) {
                    report->flags |= 0x80;
                }
            }
        } else {
            done = TRUE;
        }
        if (done) {

            ids = record->hitIds;
            if (ids != NULL) {
                for (i = 0; i < 8; i++) {
                    if (ids[i] == -1) {
                        ids[i] = id;
                        break;
                    }
                }
            }
            report->kind = 4;
            report->targetId = id;
            report->partId = partId;
            center = GetShapeCenter_0203b43c(record);
            centerCopy = center;
            switch (record->kind) {
            case 3:
            case 4:
                report->point = info.position;
                break;
            default:
                ScaleVecFx32_01ffafb4(result.distance, &result.direction, &offset);
                VEC_Add_01ff9e0c(&centerCopy, &offset, &report->point);
                break;
            }
        }
    } while (id != 0 && done != TRUE);
    return id == 0;
}
