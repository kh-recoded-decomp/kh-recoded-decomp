#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    fx32 w;
    fx32 x;
    fx32 y;
    fx32 z;
} Quaternion;

typedef struct GroupMemberWork {
    s16 state;
    s8 groupIndex;
    s8 slotIndex;
    s16 leaderLink;
    u8 pad_06[0x1E];
    VecFx32 moveDelta;
} GroupMemberWork;

typedef struct GroupObject {
    u8 pad_00[0x38];
    VecFx32 position;
} GroupObject;

typedef struct ObjectGroup {
    u8 pad_00[0x38];
    VecFx32 memberOffsets[20];
    VecFx32 center;
    VecFx32 velocity;
    Quaternion orientation;
} ObjectGroup;

extern const VecFx32 data_02053438;

extern ObjectGroup *func_ov032_020bbc60(GroupObject *object);
extern GroupMemberWork *func_ov032_020bbc78(GroupObject *object);
extern int GetRemainingRowSpan_020bc6d8(GroupObject *object);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void QuatFromRotatedAxisAngle_020bd19c(Quaternion *out, const VecFx32 *axis, int angle);
extern void multiplyFixedPointQuaternions_0202f93c(Quaternion *result, const Quaternion *left, const Quaternion *right);
extern void QuaternionToRotationMatrix_0202f808(MtxFx33 *matrix, const Quaternion *quat);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *mtx, VecFx32 *dst);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline BOOL IsZeroVec(const VecFx32 *v)
{
    return v->x == 0 && v->y == 0 && v->z == 0;
}

void RollGroupAndSteerMember_020be348(GroupObject *object, const VecFx32 *delta)
{
    ObjectGroup *group = func_ov032_020bbc60(object);
    GroupMemberWork *work = func_ov032_020bbc78(object);
    int slot = GetRemainingRowSpan_020bc6d8(object);
    int angle = 0;
    MtxFx33 rotation;
    Quaternion spin;
    VecFx32 target;
    VecFx32 diff;
    int rolled;

    if (work->leaderLink == -1) {
        rolled = VEC_Mag_01ff9f28(delta) % 0xaad0;
        if (rolled > 0) {
            angle = (u16)((rolled << 16) / 0xaad0);
        }
        QuatFromRotatedAxisAngle_020bd19c(&spin, &group->velocity, angle);
        multiplyFixedPointQuaternions_0202f93c(&group->orientation, &spin, &group->orientation);
    }
    QuaternionToRotationMatrix_0202f808(&rotation, &group->orientation);
    MTX_MultVec33_01ff9404(&group->memberOffsets[slot], &rotation, &target);
    VEC_Add_01ff9e0c(&target, &group->center, &target);
    VEC_Subtract_01ff9e3c(&target, &object->position, &diff);
    if (!IsZeroVec(&diff)) {
        work->moveDelta.x = diff.x * 17 / 100;
        work->moveDelta.z = diff.z * 17 / 100;
        work->moveDelta.y = diff.y * 80 / 100;
    } else {
        work->moveDelta = data_02053438;
    }
}
