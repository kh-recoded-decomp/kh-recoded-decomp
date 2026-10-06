#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    s32 slot0 : 8;
    s32 slot1 : 8;
    s32 slot2 : 8;
    s32 slot3 : 8;
} ByteSlots;

typedef struct {
    u8 id;
    u8 pad_01[3];
    VecFx32 position;
    s16 scale;
    u16 angle;
    u8 pad_14[0x10];
    u8 hidden;
    u8 layer;
    u16 flags;
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    void *data;
    Box bounds;
    s32 kind;
} CollisionShape;

typedef struct {
    VecFx32 center;
    fx32 radius;
} SphereStorage;

typedef struct {
    CollisionShape shape;
    VecFx32 delta;
    Box sweptBounds;
} HitVolume;

typedef struct {
    HitVolume volume;
    s16 *hitSlots;
    VecFx32 motion;
    fx32 scale;
    u16 angle;
    u8 pad_5a[2];
    int target;
} HitAttack;

typedef struct {
    s32 power;
    u8 pad_04[0xc];
    u8 reaction;
    u8 reactionLevel;
    u8 pad_12[0x12];
    u16 flags;
    u8 pad_26[2];
} HitOptions;

typedef struct {
    u8 pad_00[8];
    s32 kind;
    VecFx32 hitPos;
    u8 pad_18[0xd4 - 0x18];
    s32 mode;
    u8 pad_d8[4];
} HitScan;

typedef struct {
    u16 flags;
    u8 pad_02[0x7e];
    MtxFx33 rotation;
    VecFx32 position;
} GroupMember;

typedef struct {
    int kind;
    u8 pad_04[4];
    int soundId;
    u8 pad_0c[0x34];
    s16 mainGroup;
    s16 auraGroup;
    s16 hitGroup;
    s16 loopGroup;
    int cameraPath;
    u8 pad_4c[4];
    s16 hitSlots[8];
    VecFx32 dir;
    fx32 speed;
    int timer;
    int charge;
    int hitTimer;
    fx32 step;
    ByteSlots handles;
    u16 spin;
    u8 pad_86[2];
    ByteSlots stage;
    ByteSlots phase;
} BossObject;

typedef struct {
    u8 pad_000[4];
    u32 modeFlags;
    u8 pad_008[0x108 - 0x8];
    int hasExtraNormal;
    u8 pad_10c[0x1d4 - 0x10c];
    VecFx32 normals[15];
    u8 pad_288[0xc];
    u8 normalCount;
} ActorContacts;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1f8];
    void (*onSound)(Actor *actor, int id, int arg);
    void (*onLand)(Actor *actor, int frame);
    u8 pad_200[4];
    void (*onSignal)(Actor *actor, int signal);
    u8 pad_208[8];
    void (*onTurn)(Actor *actor, u16 angle);
    u8 pad_214[0x228 - 0x214];
    BOOL (*getTarget)(Actor *actor, VecFx32 *out);
    u8 pad_22c[0x230 - 0x22c];
    ActorContacts contacts;
    u8 pad_4c8[0x760 - 0x4c8];
    int animFrame;
    u8 pad_764[4];
    BOOL finished;
    u8 pad_76c[0x9ac - 0x76c];
    u64 flags;
    u8 player;
    u8 pad_9b5[0x9c8 - 0x9b5];
    VecFx32 pos;
    u8 pad_9d4[0xb2c - 0x9d4];
    u8 sound[0x1078 - 0xb2c];
    BossObject *boss;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setMode)(Actor *actor, int mode);
};

#define FX_MUL64(a, b) ((fx32)(((s64)(a) * (b) + 0x800) >> 12))

extern const s16 data_0205356c[];
extern const VecFx32 data_02053438;
extern const VecFx32 data_ov071_020d9660;
extern void *func_ov001_0206db78(u32 player);
extern void ComputeRootMotionDelta_020ce9d4(Actor *actor, VecFx32 *out);
extern int GetOv071PaletteEntry_020d8114(BossObject *boss);
extern BOOL SetPendingSlotFlagWithValue_0207d504(int slot, u32 value);
extern void CameraPath_Start_020c2f44(int path);
extern BOOL RestartScriptSound_020a818c(void *sound, int soundId);
extern void SetActorPaused_020d12f0(Actor *actor, int paused);
extern int GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern VecFx32 *func_ov052_020ceb54(Actor *actor);
extern void VEC_NormalizeUnchecked_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void Camera_ReturnFromPathView_020c2fac(void);
extern void SpawnEffectAboveEntity_020d8138(Actor *actor, int arg);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void AdjustVectorTowardNormal_0204ac64(VecFx32 *a, const VecFx32 *b, fx32 factor);
extern fx32 VEC_DotProduct_01ff9e6c(const VecFx32 *a, const VecFx32 *b);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *v, const VecFx32 *add, VecFx32 *dst);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern BOOL IsGroupMemberActive_020a8d1c(int groupId, int index);
extern void StopAndClearSoundEmitter_020a8e14(int groupId, int index);
extern GroupMember *GetGroupMemberData_020a8eec(int groupId, int index);
extern int FixedPointMultiply12(int left, int right);
extern void ScaleVecFx32_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern BOOL UpdateIdleTimeout_0206e1c8(void);
extern void Camera_BlendToFollowView_020c1304(s32 curveType, fx32 duration);
extern fx32 FX_Div_01ff9c84(fx32 numer, fx32 denom);
extern void MTX_RotX33_01ff9220(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_RotY33_01ff923c(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern void MTX_Concat33_01ff9270(const MtxFx33 *a, const MtxFx33 *b, MtxFx33 *ab);
extern u16 FixedPointAtan2_020062bc(int y, int x);
extern void InitRecord60_020ac0b8(HitAttack *attack);
extern void MakeSphereShape_0203ad14(CollisionShape *shape, SphereStorage *sphere, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta_0203ac70(const Box *src, Box *dst, const VecFx32 *delta);
extern void ZeroBytes0x28_020ac0f8(void *obj);
extern void ZeroAndSetField0xd4_020ac150(void *obj);
extern BOOL StepHitScan_020ac164(int type, HitAttack *attack, HitOptions *options, HitScan *scan);
extern BOOL func_ov071_020d8100(BossObject *boss);
extern BOOL HasFlagsAt0xe_020a752c(void *holder, u16 mask);
extern u16 GetFieldAt0xe_020a7558(void *obj);
extern int func_ov046_020c0d68(void);
extern void func_ov046_020c3368(int arg);

static inline void SetActorPos(Actor *actor, fx32 x, fx32 y, fx32 z)
{
    actor->pos.x = x;
    actor->pos.y = y;
    actor->pos.z = z;
}

void UpdateOv071BossState_020d836c(Actor *actor)
{
    BossObject *boss = actor->boss;
    HitScan scan;
    HitAttack attack;
    HitVolume swept;
    VecFx32 delta;
    VecFx32 launchDir;
    VecFx32 cur;
    VecFx32 vel;
    VecFx32 prev;
    MarkerRequest trailRequest;
    VecFx32 slideDir;
    VecFx32 slidePos;
    MarkerRequest riseRequest;
    MarkerRequest burstRequest;
    MarkerRequest spinRequest;
    MarkerRequest chargeRequest;
    MarkerRequest releaseRequest;
    MarkerRequest finishRequest;
    MtxFx33 spinMtx;
    MtxFx33 pitchMtx;
    MtxFx33 yawMtx;
    VecFx32 memberPos;
    VecFx32 faceDir;
    VecFx32 faceTarget;
    SphereStorage sphere;
    HitOptions options;
    MarkerRequest hitRequest;
    VecFx32 center;
    VecFx32 motion;
    VecFx32 seekDir;
    VecFx32 seekTarget;
    VecFx32 resetDir;
    MarkerRequest loopRequest;
    void *entry;
    int hitIndex;
    u16 yaw;
    int count;
    fx32 spinSpeed;
    int remaining;
    int i;
    int angle;
    GroupMember *member;
    u16 spin;
    HitScan *hit;
    ActorContacts *contacts;
    BOOL hitValid;
    BOOL found;
    fx32 limit;
    fx32 value;
    fx32 blend;
    fx32 dist;
    fx32 speed;
    int bits;
    u16 turn;
    u32 grounded;

    entry = func_ov001_0206db78(actor->player);
    if ((actor->flags & 0x200) == 0) {
        ComputeRootMotionDelta_020ce9d4(actor, &delta);
        actor->pos.y = delta.y;
        actor->pos.x += delta.x;
        actor->pos.z += delta.z;
    }
    if (boss->timer < GetOv071PaletteEntry_020d8114(boss)) {
        remaining = GetOv071PaletteEntry_020d8114(boss) - boss->timer;
    } else {
        remaining = 0;
    }
    SetPendingSlotFlagWithValue_0207d504(1, remaining / 30 + 0xfff);
    switch (boss->phase.slot0) {
    default:
        boss->phase.slot0 = 0;
    case 0:
        CameraPath_Start_020c2f44(boss->cameraPath);
        RestartScriptSound_020a818c(actor->sound, 0);
        if (actor->onSound != NULL) {
            actor->onSound(actor, 0x28, -1);
        }
        boss->timer = 0;
        boss->stage.slot3 = 1;
        boss->phase.slot0 = 1;
    case 1:
        if (actor->animFrame >= 0x10000) {
            if (actor->onLand != NULL) {
                actor->onLand(actor, 0x11000);
            }
            SetActorPaused_020d12f0(actor, 1);
            if (actor->onSignal != NULL) {
                actor->onSignal(actor, 0);
            }
            angle = GetLinkedAngleOffset_020ceb7c(actor);
            launchDir.x = -data_0205356c[angle >> 4];
            launchDir.y = 0;
            launchDir.z = -data_0205356c[(0x400 - (angle >> 4)) & 0xfff];
            VEC_NormalizeUnchecked_01ff9f88(&launchDir, &boss->dir);
            Camera_ReturnFromPathView_020c2fac();
            SpawnEffectAboveEntity_020d8138(actor, 0x5000);
            boss->speed = VEC_Mag_01ff9f28(&delta);
            boss->spin = 0;
            boss->stage.slot2 = 3;
            boss->phase.slot0 = 3;
        }
        break;
    case 3:
        if (boss->speed > 0) {
            contacts = &actor->contacts;
            if (contacts->hasExtraNormal != 0) {
                count = contacts->normalCount - 1;
            } else {
                count = contacts->normalCount;
            }
            hitIndex = -1;
            cur = boss->dir;
            prev = cur;
            for (i = 0; i < count; i++) {
                AdjustVectorTowardNormal_0204ac64(&cur, &contacts->normals[i], 0x1000);
                if (VEC_DotProduct_01ff9e6c(&cur, &data_ov071_020d9660) < 0xd6) {
                    cur.y = 0;
                    VEC_NormalizeUnchecked_01ff9f88(&cur, &cur);
                    if (hitIndex == -1 && VEC_DotProduct_01ff9e6c(&cur, &prev) < 0xfea) {
                        func_ov021_020a8ab4(&trailRequest);
                        trailRequest.id = actor->player;
                        trailRequest.layer = 0;
                        trailRequest.hidden = 0;
                        VEC_MultAdd_01ffa09c(0x1000, &prev, func_ov052_020ceb54(actor), &trailRequest.position);
                        trailRequest.position.y += 0xe66;
                        trailRequest.soundId = boss->soundId;
                        trailRequest.delay = 6;
                        hitIndex = func_ov021_020a8ca0(&trailRequest, boss->hitGroup);
                    }
                    prev = cur;
                } else {
                    cur = prev;
                }
            }
            boss->dir = cur;
        }
        ScaleVecFx32_01ffafb4(FixedPointMultiply12(boss->speed, boss->step), &boss->dir, &vel);
        vel.y = actor->pos.y;
        if ((actor->contacts.modeFlags & 4) == 0) {
            vel.y += FixedPointMultiply12(-0xcd, boss->step);
        }
        SetActorPos(actor, vel.x, vel.y, vel.z);
        if (boss->timer > GetOv071PaletteEntry_020d8114(boss) || UpdateIdleTimeout_0206e1c8()) {
            boss->stage.slot3 = 8;
            boss->phase.slot0 = 4;
            boss->phase.slot1 = 4;
        } else {
            boss->timer += boss->step;
        }
        break;
    case 4:
        SetActorPaused_020d12f0(actor, 0);
        if (actor->onSignal != NULL) {
            actor->onSignal(actor, 0x1f);
        }
        if (actor->onLand != NULL) {
            actor->onLand(actor, 0x11000);
        }
        Camera_BlendToFollowView_020c1304(3, 0x8000);
        boss->phase.slot0 = 5;
    case 5:
        if (actor->animFrame < 0x23000) {
            slidePos = actor->pos;
            slidePos.y = 0;
            blend = FX_Div_01ff9c84(actor->animFrame - 0x11000, 0x12000);
            dist = VEC_Mag_01ff9f28(&slidePos);
            speed = FixedPointMultiply12(boss->speed, boss->step);
            angle = GetLinkedAngleOffset_020ceb7c(actor);
            slideDir.x = -data_0205356c[angle >> 4];
            slideDir.z = -data_0205356c[(0x400 - (angle >> 4)) & 0xfff];
            slideDir.y = 0;
            VEC_NormalizeUnchecked_01ff9f88(&slideDir, &slideDir);
            ScaleVecFx32_01ffafb4(FX_MUL64(speed, 0x1000 - blend) + FX_MUL64(dist, blend), &slideDir, &slidePos);
            SetActorPos(actor, slidePos.x, slidePos.y, slidePos.z);
            boss->speed -= FixedPointMultiply12(0x52, boss->step);
            if (boss->speed < 0) {
                boss->speed = 0;
            }
        }
        if (actor->finished) {
            grounded = actor->contacts.modeFlags & 4;
            actor->pos.x = data_02053438.x;
            actor->pos.y = data_02053438.y;
            actor->pos.z = data_02053438.z;
            if (grounded) {
                actor->setMode(actor, 5);
                return;
            }
            actor->setMode(actor, 4);
            return;
        }
        break;
    }
    switch (boss->stage.slot3) {
    case 0:
    case 3:
    case 5:
    case 9:
        break;
    default:
        boss->stage.slot3 = 0;
        break;
    case 1:
        if (actor->animFrame < 0xd000) {
            break;
        }
        func_ov021_020a8ab4(&riseRequest);
        riseRequest.id = actor->player;
        riseRequest.layer = 0;
        riseRequest.position = *func_ov052_020ceb54(actor);
        riseRequest.position.y += 0xe66;
        riseRequest.angle = GetLinkedAngleOffset_020ceb7c(actor) + 0x8000;
        riseRequest.hidden = 0;
        riseRequest.soundId = boss->soundId;
        riseRequest.delay = 0;
        boss->handles.slot0 = func_ov021_020a8ca0(&riseRequest, boss->mainGroup);
        boss->stage.slot3 = 2;
    case 2:
        if (IsGroupMemberActive_020a8d1c(boss->mainGroup, boss->handles.slot0)) {
            break;
        }
        func_ov021_020a8ab4(&burstRequest);
        burstRequest.id = actor->player;
        burstRequest.layer = 1;
        burstRequest.position.y = 0xe66;
        burstRequest.angle = 0x8000;
        burstRequest.hidden = 3;
        burstRequest.soundId = boss->soundId;
        burstRequest.delay = 5;
        boss->handles.slot1 = func_ov021_020a8ca0(&burstRequest, boss->auraGroup);
        func_ov021_020a8ab4(&burstRequest);
        burstRequest.id = actor->player;
        burstRequest.layer = 0;
        burstRequest.flags |= 4;
        burstRequest.position = *func_ov052_020ceb54(actor);
        burstRequest.position.y += 0xe66;
        burstRequest.angle = GetLinkedAngleOffset_020ceb7c(actor) + 0x8000;
        burstRequest.hidden = 1;
        StopAndClearSoundEmitter_020a8e14(boss->mainGroup, boss->handles.slot0);
        boss->handles.slot0 = func_ov021_020a8ca0(&burstRequest, boss->mainGroup);
        boss->speed = 0xb33;
        boss->hitTimer = 0xa000;
        boss->stage.slot3 = 3;
        boss->phase.slot1 = 2;
        break;
    case 4:
        if (IsGroupMemberActive_020a8d1c(boss->auraGroup, boss->handles.slot1)) {
            break;
        }
        func_ov021_020a8ab4(&spinRequest);
        spinRequest.id = actor->player;
        spinRequest.layer = 1;
        spinRequest.flags |= 4;
        spinRequest.position.y = 0xe66;
        spinRequest.angle = 0x8000;
        spinRequest.hidden = 0;
        spinRequest.soundId = boss->soundId;
        spinRequest.delay = 2;
        StopAndClearSoundEmitter_020a8e14(boss->auraGroup, boss->handles.slot1);
        boss->handles.slot1 = func_ov021_020a8ca0(&spinRequest, boss->auraGroup);
        boss->stage.slot3 = 5;
        break;
    case 6:
        func_ov021_020a8ab4(&chargeRequest);
        chargeRequest.id = actor->player;
        chargeRequest.layer = 1;
        chargeRequest.position.y = 0xe66;
        chargeRequest.angle = 0x8000;
        chargeRequest.hidden = 1;
        chargeRequest.soundId = boss->soundId;
        chargeRequest.delay = 3;
        StopAndClearSoundEmitter_020a8e14(boss->auraGroup, boss->handles.slot1);
        boss->handles.slot1 = func_ov021_020a8ca0(&chargeRequest, boss->auraGroup);
        func_ov021_020a8ab4(&chargeRequest);
        chargeRequest.id = actor->player;
        chargeRequest.layer = 1;
        chargeRequest.angle = 0x8000;
        chargeRequest.flags |= 4;
        chargeRequest.position.y = 0xe66;
        chargeRequest.hidden = 2;
        chargeRequest.soundId = boss->soundId;
        chargeRequest.delay = 4;
        if (boss->handles.slot2 != -1) {
            StopAndClearSoundEmitter_020a8e14(boss->auraGroup, boss->handles.slot2);
        }
        boss->handles.slot2 = func_ov021_020a8ca0(&chargeRequest, boss->auraGroup);
        boss->stage.slot3 = 4;
        break;
    case 7:
        func_ov021_020a8ab4(&releaseRequest);
        releaseRequest.id = actor->player;
        releaseRequest.layer = 1;
        releaseRequest.position.y = 0xe66;
        releaseRequest.angle = 0x8000;
        releaseRequest.hidden = 3;
        releaseRequest.soundId = boss->soundId;
        releaseRequest.delay = 5;
        StopAndClearSoundEmitter_020a8e14(boss->auraGroup, boss->handles.slot1);
        boss->handles.slot1 = func_ov021_020a8ca0(&releaseRequest, boss->auraGroup);
        if (boss->handles.slot2 != -1) {
            StopAndClearSoundEmitter_020a8e14(boss->auraGroup, boss->handles.slot2);
            boss->handles.slot2 = -1;
        }
        boss->stage.slot3 = 3;
        break;
    case 8:
        func_ov021_020a8ab4(&finishRequest);
        finishRequest.id = actor->player;
        finishRequest.layer = 1;
        finishRequest.position.y = 0xe66;
        finishRequest.angle = 0x8000;
        finishRequest.hidden = 2;
        finishRequest.soundId = boss->soundId;
        finishRequest.delay = 1;
        StopAndClearSoundEmitter_020a8e14(boss->mainGroup, boss->handles.slot0);
        boss->handles.slot0 = func_ov021_020a8ca0(&finishRequest, boss->mainGroup);
        if (boss->handles.slot1 != -1) {
            StopAndClearSoundEmitter_020a8e14(boss->auraGroup, boss->handles.slot1);
            boss->handles.slot1 = -1;
        }
        if (boss->handles.slot2 != -1) {
            StopAndClearSoundEmitter_020a8e14(boss->auraGroup, boss->handles.slot2);
            boss->handles.slot2 = -1;
        }
        boss->stage.slot3 = 9;
        break;
    }
    if (boss->handles.slot0 != -1) {
        member = GetGroupMemberData_020a8eec(boss->mainGroup, boss->handles.slot0);
        yaw = GetLinkedAngleOffset_020ceb7c(actor) + 0x8000;
        spin = boss->spin;
        if (boss->stage.slot0 != 0) {
            spinSpeed = 0x23000;
        } else {
            value = FX_MUL64(FX_Div_01ff9c84(boss->charge, 0xf), 0xb33);
            if (value < boss->speed) {
                value = boss->speed;
            }
            spinSpeed = (fx32)(((s64)FX_Div_01ff9c84(value, 0x1800) * 0x394BB834C8LL + 0x80000000LL) >> 32);
            if (spinSpeed < 0x5000) {
                spinSpeed = 0x5000;
            }
        }
        memberPos = *func_ov052_020ceb54(actor);
        memberPos.y += 0xe66;
        MTX_RotX33_01ff9220(&pitchMtx, data_0205356c[spin >> 4], data_0205356c[(0x400 - (spin >> 4)) & 0xfff]);
        MTX_RotY33_01ff923c(&yawMtx, data_0205356c[yaw >> 4], data_0205356c[(0x400 - (yaw >> 4)) & 0xfff]);
        MTX_Concat33_01ff9270(&pitchMtx, &yawMtx, &spinMtx);
        member->rotation = spinMtx;
        member->flags &= ~0x20;
        member->position = memberPos;
        boss->spin += (u16)(((s64)FX_MUL64(spinSpeed, boss->step) * 0xB60B60B60BLL + 0x80000000000LL) >> 44);
    }
    switch (boss->phase.slot1) {
    default:
        boss->phase.slot1 = 0;
    case 0:
        if (actor->getTarget != NULL) {
            found = actor->getTarget(actor, &faceTarget);
        } else {
            found = FALSE;
        }
        if (found) {
            VEC_Subtract_01ff9e3c(&faceTarget, func_ov052_020ceb54(actor), &faceDir);
            faceDir.y = 0;
            if (VEC_DotProduct_01ff9e6c(&faceDir, &faceDir) > 0) {
                VEC_NormalizeUnchecked_01ff9f88(&faceDir, &faceDir);
                turn = FixedPointAtan2_020062bc(faceDir.x, faceDir.z) + 0x8000;
                if (actor->onTurn != NULL) {
                    actor->onTurn(actor, turn);
                }
            }
        }
        boss->phase.slot1 = 1;
    case 1:
        boss->speed -= FixedPointMultiply12(0x52, boss->step);
        if (boss->speed < 0) {
            boss->speed = 0;
        }
        break;
    case 2:
        spin = FixedPointAtan2_020062bc(boss->dir.x, boss->dir.z) + 0x8000;
        if (actor->onTurn != NULL) {
            actor->onTurn(actor, spin);
        }
        if (boss->speed > 0x333) {
            if (boss->hitTimer < 0xa000) {
                value = boss->hitTimer + boss->step;
            } else {
                for (i = 0; i < 8; i++) {
                    boss->hitSlots[i] = -1;
                }
                value = 0;
            }
            boss->hitTimer = value;
            center = *func_ov052_020ceb54(actor);
            center.y += 0x1800;
            InitRecord60_020ac0b8(&attack);
            ScaleVecFx32_01ffafb4(FixedPointMultiply12(boss->speed, boss->step), &boss->dir, &motion);
            MakeSphereShape_0203ad14(&swept.shape, &sphere, &center, 0x1800);
            swept.delta = motion;
            OffsetBoxByDelta_0203ac70(&swept.shape.bounds, &swept.sweptBounds, &swept.delta);
            attack.volume = swept;
            attack.hitSlots = boss->hitSlots;
            ZeroBytes0x28_020ac0f8(&options);
            options.power = func_ov071_020d8100(boss) ? 0x1b02 : 0x1200;
            options.reaction = 1;
            options.reactionLevel = 2;
            options.flags |= 0x80;
            options.flags |= 0x800;
            hit = &scan;
            ZeroAndSetField0xd4_020ac150(hit);
            while (StepHitScan_020ac164(actor->player, &attack, &options, hit)) {
                hitValid = FALSE;
                switch (hit->kind) {
                case 3:
                case 4:
                    hitValid = TRUE;
                    break;
                }
                if (hitValid) {
                    func_ov021_020a8ab4(&hitRequest);
                    hitRequest.id = actor->player;
                    hitRequest.layer = 0;
                    hitRequest.hidden = 0;
                    hitRequest.position = hit->hitPos;
                    hitRequest.soundId = boss->soundId;
                    hitRequest.delay = 6;
                    func_ov021_020a8ca0(&hitRequest, boss->hitGroup);
                }
            }
        }
        limit = func_ov071_020d8100(boss) ? 0xa66 : 0x800;
        if (boss->speed > limit) {
            boss->speed -= FixedPointMultiply12(0x52, boss->step);
            if (boss->speed < 0x333) {
                boss->speed = 0x333;
            }
        } else if (HasFlagsAt0xe_020a752c(entry, 1)) {
            found = FALSE;
            boss->charge = 0;
            boss->stage.slot0 = 0;
            boss->stage.slot2 = 1;
            boss->stage.slot1 = 2;
            boss->stage.slot3 = 4;
            boss->phase.slot1 = 3;
            if (actor->getTarget != NULL) {
                found = actor->getTarget(actor, &seekTarget);
            }
            if (found) {
                VEC_Subtract_01ff9e3c(&seekTarget, func_ov052_020ceb54(actor), &seekDir);
                seekDir.y = 0;
                if (VEC_DotProduct_01ff9e6c(&seekDir, &seekDir) > 0) {
                    VEC_NormalizeUnchecked_01ff9f88(&seekDir, &seekDir);
                    turn = FixedPointAtan2_020062bc(seekDir.x, seekDir.z) + 0x8000;
                    if (actor->onTurn != NULL) {
                        actor->onTurn(actor, turn);
                    }
                }
            }
        }
        break;
    case 3:
        if (HasFlagsAt0xe_020a752c(entry, 1)) {
            if (boss->stage.slot0 == 0 && boss->charge >= 15.0f) {
                boss->charge = 0xf;
                boss->stage.slot0 = 1;
                boss->stage.slot3 = 6;
            } else {
                boss->charge += boss->step;
            }
            angle = GetLinkedAngleOffset_020ceb7c(actor);
            bits = GetFieldAt0xe_020a7558(entry) & 0x30;
            switch (bits) {
            case 0x20:
                if (actor->onTurn != NULL) {
                    actor->onTurn(actor, angle + 0x3e9);
                }
                break;
            case 0x10:
                if (actor->onTurn != NULL) {
                    actor->onTurn(actor, angle - 0x3e9);
                }
                break;
            }
            boss->speed -= FixedPointMultiply12(0x52, boss->step);
            if (boss->speed < 0x333) {
                boss->speed = 0x333;
            }
        } else {
            value = FX_MUL64(FX_Div_01ff9c84(boss->charge, 0xf), 0xb33);
            if (value > 0x333) {
                if (value >= 0xb33) {
                    value = 0xb33;
                }
            } else {
                value = 0x333;
            }
            boss->speed = value;
            angle = GetLinkedAngleOffset_020ceb7c(actor);
            resetDir.x = -data_0205356c[angle >> 4];
            resetDir.z = -data_0205356c[(0x400 - (angle >> 4)) & 0xfff];
            resetDir.y = 0;
            VEC_NormalizeUnchecked_01ff9f88(&resetDir, &boss->dir);
            boss->hitTimer = 0xa000;
            boss->charge = 0;
            boss->stage.slot0 = 0;
            boss->stage.slot2 = 3;
            boss->stage.slot1 = 0;
            boss->stage.slot3 = 7;
            boss->phase.slot1 = 2;
        }
        break;
    case 4:
        boss->stage.slot1 = 0;
        boss->phase.slot1 = 5;
        break;
    case 5:
        break;
    }
    switch (boss->stage.slot1) {
    case 0:
        if (boss->handles.slot3 != -1) {
            StopAndClearSoundEmitter_020a8e14(boss->loopGroup, boss->handles.slot3);
            boss->handles.slot3 = -1;
        }
        boss->stage.slot1 = 1;
        break;
    case 2:
        if (boss->handles.slot3 == -1) {
            func_ov021_020a8ab4(&loopRequest);
            loopRequest.id = actor->player;
            loopRequest.layer = 1;
            loopRequest.flags |= 4;
            loopRequest.position.y = 0xe66;
            loopRequest.angle = 0x8000;
            loopRequest.hidden = 0;
            boss->handles.slot3 = func_ov021_020a8ca0(&loopRequest, boss->loopGroup);
        }
        boss->stage.slot1 = 3;
        break;
    case 1:
    case 3:
        break;
    }
    switch (boss->stage.slot2) {
    case 0:
    case 2:
    case 4:
        break;
    case 1:
        SpawnEffectAboveEntity_020d8138(actor, 0x5000);
        boss->stage.slot2 = 2;
        break;
    case 3:
        if (func_ov046_020c0d68() != 2) {
            func_ov046_020c3368(1);
            boss->stage.slot2 = 4;
        }
        break;
    }
}
