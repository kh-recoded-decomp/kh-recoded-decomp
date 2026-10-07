#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    VecFx32 *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} SweptShape;

typedef struct {
    u8 data[0x2c];
} CylinderStorage;

typedef struct {
    u8 pad_000[0xc0];
    VecFx32 normals[16];
    u8 count;
    u8 pad_181[0x23];
} QueryWorkspace;

typedef struct {
    void *func;
    void *arg;
} QueryCallback;

typedef struct {
    u32 words[0x12];
    QueryCallback filter;
    QueryCallback contact;
    u32 tail[2];
} CollisionQuery;

typedef struct {
    u8 pad_00[4];
    s32 sideHit;
    s32 floorHit;
    u8 pad_0c[0x2c];
    VecFx32 position;
} SweepHit;

typedef struct {
    fx32 distance;
    VecFx32 direction;
    u32 pad_10[2];
} Movement;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 hidden;
    u8 layer;
    u16 flags;
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct {
    u16 flags;
    u8 pad_02[0x7e];
    MtxFx33 rotation;
    VecFx32 position;
} GroupMember;

typedef struct {
    s32 ringSlot : 8;
    s32 auraSlot : 8;
    s32 pillarSlot : 6;
    s32 grounded : 1;
    s32 unk_23 : 1;
    s32 pillarState : 8;
} RideSlots;

typedef struct {
    s32 auraState : 8;
    s32 ringState : 8;
    s32 introState : 8;
    s32 rideState : 8;
} RideStates;

typedef struct {
    u8 pad_00[8];
    int soundId;
    u8 pad_0c[0x34];
    s16 auraGroup;
    s16 pillarGroup;
    u8 pad_44[2];
    s16 burstGroup;
    s16 ringGroup;
    u8 pad_4a[2];
    int cameraPath;
    VecFx32 origin;
    VecFx32 position;
    int counter;
    fx32 speed;
    fx32 interval;
    fx32 timer;
    fx32 rate;
    u8 pad_7c[4];
    u16 heading;
    u8 pad_82[2];
    RideSlots slots;
    RideStates states;
} RideTask;

typedef struct {
    u8 pad_00[4];
    u8 anim[1];
} RideModel;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1f8];
    void (*onEvent)(Actor *actor, int event, int arg);
    void (*onLand)(Actor *actor, int frame);
    u8 pad_200[0x210 - 0x200];
    void (*setHeading)(Actor *actor, u16 angle);
    u8 pad_214[0x228 - 0x214];
    BOOL (*getFootPosition)(Actor *actor, VecFx32 *out);
    u8 pad_22c[0x230 - 0x22c];
    RideModel *model;
    u32 stateFlags;
    u8 pad_238[0x768 - 0x238];
    s32 finished;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 player;
    u8 pad_9b5[0x9c8 - 0x9b5];
    fx32 posX;
    fx32 posY;
    fx32 posZ;
    u8 pad_9d4[0xb2c - 0x9d4];
    u8 sound[0x1078 - 0xb2c];
    RideTask *task;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setMode)(Actor *actor, int mode);
};

extern const VecFx32 data_02053438;
extern const s16 data_0205356c[];

extern void ComputeRootMotionDelta_020ce9d4(Actor *actor, VecFx32 *out);
extern int GetObjectPaletteValue_020d8114(RideTask *task);
extern BOOL SetPendingSlotFlagWithValue_0207d504(int slot, u32 value);
extern void RestartScriptSound_020a818c(void *sound, int arg);
extern VecFx32 *func_ov052_020ceb54(Actor *actor);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_Normalize_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern void CameraPath_Start_020c2f44(int path);
extern int Anim_GetFrame_0202f4a0(void *anim, int track);
extern void Camera_ReturnFromPathView_020c2fac(void);
extern void func_ov046_020c29b0(VecFx32 *target);
extern void Camera_SetFollowSuspended_020c29c0(int suspended);
extern void func_ov046_020c2a84(int enabled);
extern BOOL UpdateIdleTimeout_0206e1c8(void);
extern void Camera_RefreshTargetHeading_020c2bac(void);
extern u32 Camera_GetDriftHeading_020c14fc(void);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern BOOL IsGroupMemberActive_020a8d1c(int groupId, int handle);
extern void StopAndClearSoundEmitter_020a8e14(int groupId, int handle);
extern void SetSlotEntryValue_020a8f4c(int groupId, int handle, int value);
extern GroupMember *GetGroupMemberData_020a8eec(int groupId, int handle);
extern void *func_ov001_0206db78(int player);
extern BOOL HasFlagsAt0xe_020a752c(void *holder, u16 mask);
extern u16 GetFieldAt0xe_020a7558(void *holder);
extern void EmitPillarHitScan_020d8300(RideTask *task, Actor *actor, const VecFx32 *pos);
extern void Camera_StartDriftAlongView_020c0fd4(int speed, int duration);
extern u16 GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_MultVec33_01ff9404(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern u32 random_next_scaled_0202aa04(u32 upperBound);
extern BOOL func_ov072_020d8100(RideTask *task);
extern CollisionShape InitCylinderShape_0203aeac(CylinderStorage *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void CollisionQuery_Init_02034c74(CollisionQuery *query, u16 id, void *actor, u8 kind, u8 unk3C, u8 unk3D, void *shape, QueryWorkspace *workspace, void *filter);
extern void func_02031fec(QueryWorkspace *workspace, VecFx32 *normal);
extern SweepHit *SweepWorldCollision_020364a0(CollisionQuery *query);
extern void NegateVecFx32_0204aa40(VecFx32 *vec);
extern VecFx32 ResolveSlideMovement_0203deac(const Movement *move, const VecFx32 *normals, int count, u32 *outType, u8 *outPair, u8 *outList, const VecFx32 *motion, void *extraA, void *extraB);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern BOOL IsEventActionAllowed_020d847c(void *event);
extern BOOL FlattenContactNormal_020d84e4(void *contact, void *plane);
extern BOOL SnapContactNormalUp_020d84b0(void *contact, void *plane);

static inline void SetVec(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static inline fx32 FxMul(fx32 a, fx32 b)
{
    return (fx32)(((s64)a * b + 0x800) >> 12);
}

static inline u16 DegToIndex(fx32 degrees)
{
    return (u16)(((s64)degrees * 0xB60B60B60BLL + 0x80000000000LL) >> 44);
}

static inline void SetActorHeading(Actor *actor, u16 angle)
{
    if (actor->setHeading != NULL) {
        actor->setHeading(actor, angle);
    }
}

void UpdatePillarRide_020d8528(Actor *actor)
{
    VecFx32 rootDelta;
    BOOL grounded;
    CollisionQuery sweep;
    QueryWorkspace workspace;
    VecFx32 heading;
    VecFx32 footPos;
    MarkerRequest request1;
    MarkerRequest request2;
    MarkerRequest request3;
    MarkerRequest request4;
    MarkerRequest request5;
    MarkerRequest request6;
    MarkerRequest request7;
    MarkerRequest request8;
    MarkerRequest request9;
    MarkerRequest request10;
    MtxFx33 rot;
    VecFx32 offset;
    VecFx32 scatter;
    CylinderStorage cylinder;
    MtxFx33 driftRot;
    VecFx32 target;
    VecFx32 dir;
    VecFx32 pos;
    VecFx32 motion;
    VecFx32 hitOffset;
    VecFx32 pushNormal;
    VecFx32 top;
    VecFx32 bottom;
    Movement move;
    VecFx32 flat;
    MtxFx33 endRot;
    VecFx32 markerPos1;
    VecFx32 markerPos2;
    SweptShape sweptCopy;
    fx32 speed;
    u16 input;
    RideTask *task = actor->task;
    fx32 y;
    BOOL pushed;
    SweepHit *hit;
    int state;

    ComputeRootMotionDelta_020ce9d4(actor, &rootDelta);
    actor->posY = rootDelta.y;
    actor->posX += rootDelta.x;
    actor->posZ += rootDelta.z;
    SetPendingSlotFlagWithValue_0207d504(1, (task->counter < GetObjectPaletteValue_020d8114(task) ? GetObjectPaletteValue_020d8114(task) - task->counter : 0) / 30 + 0xfff);

    switch (task->states.introState) {
    case 0:
        RestartScriptSound_020a818c(actor->sound, 0);
        if (actor->onEvent != NULL) {
            actor->onEvent(actor, 0x29, -1);
        }
        if ((actor->getFootPosition != NULL ? actor->getFootPosition(actor, &footPos) : FALSE) != FALSE) {
            VEC_Subtract_01ff9e3c(&footPos, func_ov052_020ceb54(actor), &heading);
            heading.y = 0;
            if (VEC_DotProduct_01ff9e6c(&heading, &heading) > 0) {
                VEC_NormalizeUnchecked_01ff9f88(&heading, &heading);
                SetActorHeading(actor, FixedPointAtan2_020062bc(heading.x, heading.z) + 0x8000);
            }
        }
        CameraPath_Start_020c2f44(task->cameraPath);
        task->origin = *func_ov052_020ceb54(actor);
        task->position = task->origin;
        task->slots.grounded = 0;
        task->states.auraState = 1;
        task->states.ringState = 1;
        task->states.introState = 1;
    case 1:
        if (Anim_GetFrame_0202f4a0(actor->model->anim, 0) < 0x17000) {
            break;
        }
        Camera_ReturnFromPathView_020c2fac();
        func_ov046_020c29b0(&task->position);
        Camera_SetFollowSuspended_020c29c0(1);
        func_ov046_020c2a84(1);
        task->states.introState = 2;
        task->states.rideState = 2;
    case 2:
        if (task->counter >= GetObjectPaletteValue_020d8114(task) || UpdateIdleTimeout_0206e1c8()) {
            Camera_RefreshTargetHeading_020c2bac();
            task->states.introState = 3;
            task->states.rideState = 4;
        } else {
            task->counter += task->rate;
        }
    case 3: {
        int over = Anim_GetFrame_0202f4a0(actor->model->anim, 0) - 0x27000;

        if (over > 0 && actor->onLand != NULL) {
            actor->onLand(actor, over + 0x17000);
        }
        break;
    }
    case 4:
        task->states.introState = 5;
    case 5:
        if (actor->finished) {
            if (actor->stateFlags & 4) {
                actor->setMode(actor, 5);
            } else {
                actor->setMode(actor, 4);
            }
            Camera_SetFollowSuspended_020c29c0(0);
            func_ov046_020c2a84(0);
            return;
        }
        break;
    }

    switch (task->slots.pillarState) {
    default:
        task->slots.pillarState = 0;
        break;
    case 0:
        break;
    case 1: {
        func_ov021_020a8ab4(&request1);
        request1.id = actor->player;
        request1.layer = 0;
        request1.position = task->position;
        request1.position.y += 0x800;
        request1.hidden = 0;
        task->slots.pillarSlot = func_ov021_020a8ca0(&request1, task->pillarGroup);
        task->heading = Camera_GetDriftHeading_020c14fc();
        task->slots.pillarState = 2;
    }
    case 2:
        if (!IsGroupMemberActive_020a8d1c(task->pillarGroup, task->slots.pillarSlot)) {
            func_ov021_020a8ab4(&request2);
            request2.id = actor->player;
            request2.layer = 0;
            request2.flags |= 4;
            request2.position = task->position;
            request2.position.y += 0x800;
            request2.hidden = 1;
            StopAndClearSoundEmitter_020a8e14(task->pillarGroup, task->slots.pillarSlot);
            task->slots.auraSlot = func_ov021_020a8ca0(&request2, task->pillarGroup);
            task->slots.pillarState = 3;
        }
        break;
    case 3:
        if (task->states.rideState == 3) {
            break;
        }
    case 4:
        SetSlotEntryValue_020a8f4c(task->pillarGroup, task->slots.pillarSlot, 0);
        task->slots.pillarState = 5;
    case 5:
        if (!IsGroupMemberActive_020a8d1c(task->pillarGroup, task->slots.pillarSlot)) {
            func_ov021_020a8ab4(&request3);
            request3.id = actor->player;
            request3.layer = 0;
            request3.position = task->position;
            request3.position.y += 0x800;
            request3.hidden = 2;
            StopAndClearSoundEmitter_020a8e14(task->pillarGroup, task->slots.pillarSlot);
            task->slots.pillarSlot = func_ov021_020a8ca0(&request3, task->pillarGroup);
            task->slots.pillarState = 6;
        }
        break;
    case 6:
        if (!IsGroupMemberActive_020a8d1c(task->pillarGroup, task->slots.pillarSlot)) {
            StopAndClearSoundEmitter_020a8e14(task->pillarGroup, task->slots.pillarSlot);
            task->slots.pillarSlot = -1;
            task->slots.pillarState = 0;
        }
        break;
    }

    switch (task->states.auraState) {
    default:
        task->states.auraState = 0;
        break;
    case 0:
    case 3:
        break;
    case 1: {
        func_ov021_020a8ab4(&request4);
        request4.id = actor->player;
        request4.layer = 0;
        request4.position = task->position;
        request4.hidden = 0;
        request4.position.y += 0x800;
        request4.soundId = task->soundId;
        request4.delay = 0;
        task->slots.auraSlot = func_ov021_020a8ca0(&request4, task->auraGroup);
        task->states.auraState = 2;
    }
    case 2:
        if (!IsGroupMemberActive_020a8d1c(task->auraGroup, task->slots.auraSlot)) {
            func_ov021_020a8ab4(&request5);
            request5.id = actor->player;
            request5.layer = 0;
            request5.flags |= 4;
            request5.position = task->position;
            request5.position.y += 0x800;
            request5.hidden = 1;
            StopAndClearSoundEmitter_020a8e14(task->auraGroup, task->slots.auraSlot);
            task->slots.auraSlot = func_ov021_020a8ca0(&request5, task->auraGroup);
            task->states.auraState = 3;
        }
        break;
    case 4:
        SetSlotEntryValue_020a8f4c(task->auraGroup, task->slots.auraSlot, 0);
        task->states.auraState = 5;
    case 5:
        if (!IsGroupMemberActive_020a8d1c(task->auraGroup, task->slots.auraSlot)) {
            func_ov021_020a8ab4(&request6);
            request6.id = actor->player;
            request6.layer = 0;
            request6.position = task->position;
            request6.position.y += 0x800;
            request6.hidden = 2;
            StopAndClearSoundEmitter_020a8e14(task->auraGroup, task->slots.auraSlot);
            task->slots.auraSlot = func_ov021_020a8ca0(&request6, task->auraGroup);
            task->states.auraState = 6;
        }
        break;
    case 6:
        if (!IsGroupMemberActive_020a8d1c(task->auraGroup, task->slots.auraSlot)) {
            StopAndClearSoundEmitter_020a8e14(task->auraGroup, task->slots.auraSlot);
            task->slots.auraSlot = -1;
            task->states.auraState = 0;
        }
        break;
    }

    switch (task->states.ringState) {
    default:
        task->states.ringState = 0;
        break;
    case 0:
    case 3:
        break;
    case 1: {
        func_ov021_020a8ab4(&request7);
        request7.id = actor->player;
        request7.layer = 1;
        request7.position.y += 0x1400;
        request7.hidden = 0;
        task->slots.ringSlot = func_ov021_020a8ca0(&request7, task->ringGroup);
        task->states.ringState = 2;
    }
    case 2:
        if (!IsGroupMemberActive_020a8d1c(task->ringGroup, task->slots.ringSlot)) {
            func_ov021_020a8ab4(&request8);
            request8.id = actor->player;
            request8.layer = 1;
            request8.flags |= 4;
            request8.position.y += 0x1400;
            request8.hidden = 1;
            StopAndClearSoundEmitter_020a8e14(task->ringGroup, task->slots.ringSlot);
            task->slots.ringSlot = func_ov021_020a8ca0(&request8, task->ringGroup);
            task->states.ringState = 3;
        }
        break;
    case 4:
        SetSlotEntryValue_020a8f4c(task->ringGroup, task->slots.ringSlot, 0);
        task->states.ringState = 5;
    case 5:
        if (!IsGroupMemberActive_020a8d1c(task->ringGroup, task->slots.ringSlot)) {
            func_ov021_020a8ab4(&request9);
            request9.id = actor->player;
            request9.layer = 1;
            request9.position.y += 0x1400;
            request9.hidden = 2;
            StopAndClearSoundEmitter_020a8e14(task->ringGroup, task->slots.ringSlot);
            task->slots.ringSlot = func_ov021_020a8ca0(&request9, task->ringGroup);
            task->states.ringState = 6;
        }
        break;
    case 6:
        if (!IsGroupMemberActive_020a8d1c(task->ringGroup, task->slots.ringSlot)) {
            StopAndClearSoundEmitter_020a8e14(task->ringGroup, task->slots.ringSlot);
            task->slots.ringSlot = -1;
            task->states.ringState = 0;
        }
        break;
    }

    switch (task->states.rideState) {
    default:
        task->states.rideState = 0;
    case 0:
        task->states.rideState = 1;
        break;
    case 1:
    case 5:
        break;
    case 2:
        if (task->slots.pillarState == 0 && HasFlagsAt0xe_020a752c(func_ov001_0206db78(actor->player), 1)) {
            task->speed = 0;
            task->interval = 0xf000;
            task->timer = 0;
            task->slots.pillarState = 1;
            task->states.rideState = 3;
        }
        break;
    case 3:
        if (HasFlagsAt0xe_020a752c(func_ov001_0206db78(actor->player), 1)) {
            task->speed += task->rate;
            if (task->speed > 0x3c000) {
                task->speed = 0x3c000;
            }
            task->timer -= task->rate;
        } else {
            task->states.rideState = 2;
        }
        break;
    case 4:
        if (task->slots.pillarState == 0) {
            task->states.auraState = 4;
            task->states.ringState = 4;
            task->states.introState = 4;
            task->states.rideState = 5;
        }
        break;
    }

    if (task->slots.pillarState == 3) {
        if (task->timer <= 0) {
            int handle;
            int index;
            u16 angle;

            EmitPillarHitScan_020d8300(task, actor, &task->position);
            Camera_StartDriftAlongView_020c0fd4(0x19a, 0x5000);
            task->interval -= 0x2000;
            if (task->interval < 0x5000) {
                task->interval = 0x5000;
            }
            task->timer = task->interval;
            angle = GetLinkedAngleOffset_020ceb7c(actor) + 0x8000;
            offset.x = 0;
            offset.y = 0x333;
            offset.z = 0x800;
            index = angle >> 4;
            MTX_RotY33_01ff923c(&rot, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
            MTX_MultVec33_01ff9404(&offset, &rot, &offset);
            VEC_Add_01ff9e0c(&offset, func_ov052_020ceb54(actor), &offset);
            func_ov021_020a8ab4(&request10);
            request10.id = actor->player;
            request10.layer = 0;
            request10.position = offset;
            request10.hidden = 0;
            handle = func_ov021_020a8ca0(&request10, task->burstGroup);
            if (handle != -1) {
                GroupMember *member = GetGroupMemberData_020a8eec(task->burstGroup, handle);

                index = (u16)random_next_scaled_0202aa04(0xffff) >> 4;
                MTX_RotY33_01ff923c(&rot, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
                member->rotation = rot;
                member->flags &= ~0x20;
            }
        } else if (task->interval <= 0x5000) {
            scatter.x = 0x3000 - random_next_scaled_0202aa04(0x6000);
            scatter.y = 0;
            scatter.z = 0x3000 - random_next_scaled_0202aa04(0x6000);
            VEC_Add_01ff9e0c(&scatter, &task->position, &scatter);
            EmitPillarHitScan_020d8300(task, actor, &scatter);
        }
    }

    pushed = FALSE;
    grounded = FALSE;
    state = 0;
    input = GetFieldAt0xe_020a7558(func_ov001_0206db78(actor->player));
    do {
        switch (state) {
        case 0:
        default:
            pos = task->position;
            motion = data_02053438;
            y = pos.y;
            switch (task->states.rideState) {
            case 2:
                speed = func_ov072_020d8100(task) ? 0x333 : 0x19a;
                break;
            case 3:
                speed = func_ov072_020d8100(task) ? 0x19a : 0xcd;
                break;
            default:
                speed = 0;
                break;
            }
        case 1:
            if ((input & 0xf0) != 0 && speed > 0) {
                int index;

                dir = data_02053438;
                switch (input & 0x30) {
                case 0x20:
                    dir.x = -0x1000;
                    break;
                case 0x10:
                    dir.x = 0x1000;
                    break;
                }
                switch (input & 0xc0) {
                case 0x40:
                    dir.z = -0x1000;
                    break;
                case 0x80:
                    dir.z = 0x1000;
                    break;
                }
                VEC_NormalizeUnchecked_01ff9f88(&dir, &dir);
                index = (u16)Camera_GetDriftHeading_020c14fc() >> 4;
                MTX_RotY33_01ff923c(&driftRot, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
                MTX_MultVec33_01ff9404(&dir, &driftRot, &dir);
                ScaleVecFx32_01ffafb4(speed, &dir, &motion);
                VEC_Add_01ff9e0c(&motion, &pos, &target);
                VEC_Subtract_01ff9e3c(&target, &task->origin, &dir);
                dir.y = 0;
                if (VEC_Mag_01ff9f28(&dir) > 0x14000 && VEC_DotProduct_01ff9e6c(&motion, &dir) > 0) {
                    VEC_NormalizeUnchecked_01ff9f88(&dir, &dir);
                    VEC_MultAdd_01ffa09c(0x14000, &dir, &task->origin, &target);
                    VEC_Subtract_01ff9e3c(&target, &pos, &motion);
                    motion.y = 0;
                    pushNormal.x = -dir.x;
                    pushNormal.y = 0;
                    pushNormal.z = -dir.z;
                    pushed = TRUE;
                }
            }
            state = 2;
        case 2:
        case 3: {
            VecFx32 base;
            QueryCallback filter;
            VecFx32 axis;
            VecFx32 diff;
            SweptShape swept;
            CollisionShape shape;
            CollisionQuery query;
            QueryCallback contact;

            base = pos;
            bottom = base;
            top = base;
            bottom.y = y;
            top.y = y + 0x1000;
            VEC_Subtract_01ff9e3c(&top, &bottom, &diff);
            axis = diff;
            shape = InitCylinderShape_0203aeac(&cylinder, &bottom, &top, &axis, VEC_Normalize_01ffaff4(&axis, &axis), 0x1000);
            swept.shape = shape;
            swept.delta = motion;
            OffsetBoxByDelta_0203ac70(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
            sweptCopy = swept;
            CollisionQuery_Init_02034c74(&query, 0, actor->model, 0xb, 0, 1, &sweptCopy, &workspace, NULL);
            sweep = query;
            filter.arg = NULL;
            filter.func = IsEventActionAllowed_020d847c;
            sweep.filter = filter;
            contact.func = FlattenContactNormal_020d84e4;
            contact.arg = NULL;
            sweep.contact = contact;
            if (pushed) {
                func_02031fec(&workspace, &pushNormal);
            }
            hit = SweepWorldCollision_020364a0(&sweep);
            if (hit == NULL) {
                goto drop;
            }
            switch (state) {
            case 2:
            default: {
                VecFx32 axis3;
                VecFx32 diff3;
                CollisionShape shape3;
                SweptShape swept3;
                CollisionQuery query3;

                VEC_Subtract_01ff9e3c(&hit->position, &pos, &hitOffset);
                hitOffset.y = 0;
                SetVec(&dir, 0, task->origin.y + 0x3000 - pos.y, 0);
                VEC_Subtract_01ff9e3c(&top, &bottom, &diff3);
                axis3 = diff3;
                shape3 = InitCylinderShape_0203aeac(&cylinder, &bottom, &top, &axis3, VEC_Normalize_01ffaff4(&axis3, &axis3), 0x1000);
                swept3.shape = shape3;
                swept3.delta = dir;
                OffsetBoxByDelta_0203ac70(&swept3.shape.bounds, &swept3.sweptBounds, &swept3.delta);
                sweptCopy = swept3;
                CollisionQuery_Init_02034c74(&query3, 0, actor->model, 4, 0, 1, &sweptCopy, &workspace, NULL);
                sweep = query3;
                hit = SweepWorldCollision_020364a0(&sweep);
                if (hit != NULL) {
                    y = hit->position.y;
                } else {
                    y = (pos.y < task->origin.y ? pos.y : task->origin.y) + 0x3000;
                }
                state = 3;
                break;
            }
            case 3:
                y = pos.y;
                state = 4;
                motion = hitOffset;
                break;
            }
            break;
        }
        case 4:
        drop: {
            VecFx32 base;
            VecFx32 axis;
            VecFx32 diff;
            QueryCallback filter;
            CollisionShape shape;
            SweptShape swept;
            CollisionQuery query;
            QueryCallback contact;

            VEC_Add_01ff9e0c(&pos, &motion, &target);
            base = target;
            bottom = base;
            top = base;
            bottom.y = y;
            top.y = y + 0x1000;
            SetVec(&dir, 0, task->origin.y - 0x3000 - y, 0);
            VEC_Subtract_01ff9e3c(&top, &bottom, &diff);
            axis = diff;
            shape = InitCylinderShape_0203aeac(&cylinder, &bottom, &top, &axis, VEC_Normalize_01ffaff4(&axis, &axis), 0x1000);
            swept.shape = shape;
            swept.delta = dir;
            OffsetBoxByDelta_0203ac70(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
            sweptCopy = swept;
            CollisionQuery_Init_02034c74(&query, 0, actor->model, (task->slots.grounded ? 0 : 2) | 9, 0, 1, &sweptCopy, &workspace, NULL);
            sweep = query;
            filter.arg = NULL;
            filter.func = IsEventActionAllowed_020d847c;
            sweep.filter = filter;
            contact.func = SnapContactNormalUp_020d84b0;
            contact.arg = NULL;
            sweep.contact = contact;
            hit = SweepWorldCollision_020364a0(&sweep);
            if (hit != NULL) {
                grounded = (hit->sideHit != 0 && hit->floorHit == 0) ? TRUE : FALSE;
                if (!task->slots.grounded || grounded) {
                    pos.y = hit->position.y;
                }
            } else {
                pos.y = task->origin.y - 0x3000;
                grounded = TRUE;
            }
        }
        case 5: {
            SweptShape swept;
            VecFx32 axis;
            CollisionQuery query;
            VecFx32 diff;
            QueryCallback filter;
            CollisionShape shape;
            QueryCallback contact;
            VecFx32 base;

            base = pos;
            bottom = base;
            top = base;
            top.y = bottom.y + 0x1000;
            VEC_Subtract_01ff9e3c(&top, &bottom, &diff);
            axis = diff;
            shape = InitCylinderShape_0203aeac(&cylinder, &bottom, &top, &axis, VEC_Normalize_01ffaff4(&axis, &axis), 0x1000);
            swept.shape = shape;
            swept.delta = motion;
            OffsetBoxByDelta_0203ac70(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
            sweptCopy = swept;
            CollisionQuery_Init_02034c74(&query, 0, actor->model, 0xa, 0, 1, &sweptCopy, &workspace, NULL);
            sweep = query;
            filter.func = IsEventActionAllowed_020d847c;
            filter.arg = NULL;
            sweep.filter = filter;
            contact.func = FlattenContactNormal_020d84e4;
            contact.arg = NULL;
            sweep.contact = contact;
            if (pushed) {
                func_02031fec(&workspace, &pushNormal);
            }
            hit = SweepWorldCollision_020364a0(&sweep);
            if (hit != NULL) {
                pos.x = hit->position.x;
                pos.z = hit->position.z;
                if (!pushed) {
                    VecFx32 fromOrigin;
                    VecFx32 sum;
                    fx32 length;
                    VecFx32 slide;

                    VEC_Subtract_01ff9e3c(&pos, &task->origin, &fromOrigin);
                    flat = fromOrigin;
                    flat.y = 0;
                    length = VEC_Normalize_01ffaff4(&flat, &move.direction);
                    if (length > 0x14000) {
                        move.distance = length - 0x14000;
                        NegateVecFx32_0204aa40(&move.direction);
                        slide = ResolveSlideMovement_0203deac(&move, workspace.normals, workspace.count, NULL, NULL, NULL, &motion, NULL, NULL);
                        VEC_Add_01ff9e0c(&pos, &slide, &sum);
                        pos = sum;
                    }
                }
            } else {
                pos.x += motion.x;
                pos.z += motion.z;
            }
            state = 6;
        }
        case 6:
            task->position = pos;
            task->slots.grounded = grounded;
            break;
        }
    } while (state != 6);

    if (task->slots.pillarSlot != -1) {
        GroupMember *member = GetGroupMemberData_020a8eec(task->pillarGroup, task->slots.pillarSlot);
        u32 step;
        int index;
        int angle = task->heading;

        markerPos1 = task->position;
        markerPos1.y += 0x800;
        member->position = markerPos1;
        index = angle >> 4;
        MTX_RotY33_01ff923c(&endRot, data_0205356c[index], data_0205356c[(0x400 - index) & 0xfff]);
        member->rotation = endRot;
        member->flags &= ~0x20;
        step = DegToIndex(FxMul(FX_Div_01ff9c84(task->speed, 0x3c000), 0x2d000));
        if (step <= 0x1000) {
            step = 0x1000;
        }
        task->heading = angle + FxMul(task->rate, step);
    }
    if (task->slots.auraSlot != -1) {
        GroupMember *member = GetGroupMemberData_020a8eec(task->auraGroup, task->slots.auraSlot);

        markerPos2 = task->position;
        markerPos2.y += 0x800;
        member->position = markerPos2;
    }
}
