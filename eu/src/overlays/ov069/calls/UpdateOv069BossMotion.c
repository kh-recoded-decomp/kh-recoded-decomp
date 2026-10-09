#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 mode : 8;
    s32 step : 8;
    s32 count : 16;
} IntroCounter;

typedef struct {
    u8 id;
    u8 pad_01[0x11];
    u16 angle;
    u8 pad_14[0x10];
    u8 hidden;
    u8 layer;
    u16 flags;
    u16 soundId;
    u16 delay;
} MarkerRequest;

typedef struct {
    u8 pad_00[0x90];
} AnimEntry;

typedef struct {
    void (*callback)();
    void *context;
    u8 pad_08[0x10];
    u16 lowFlags : 2;
    u16 hitOnce : 1;
    u16 midFlags : 9;
    u16 mirrored : 1;
    u16 highFlags : 3;
    u8 pad_1a[6];
} SlotEntry;

typedef struct {
    u8 pad_00[8];
    int soundId;
    u8 pad_0c[0x40];
    s16 group;
    u8 pad_4e[0x1e];
    AnimEntry *entries;
    u8 pad_70[0x11];
    s8 slot;
    u8 pad_82[2];
    u8 cameraPath[0x60];
    VecFx32 dir;
    fx32 speed;
    u8 pad_f4[4];
    int seqHandle;
    IntroCounter counter;
} SceneObject;

typedef struct {
    u8 pad_00[0x12];
    u16 field12;
} InputEntry;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x94];
    u16 angle;
    u8 pad_096[0xbc - 0x96];
    VecFx32 center;
    u8 pad_0c8[0x1f0 - 0xc8];
    int (*playSound)(Actor *actor, int id, int a, int b);
    u8 pad_1f4[0x1fc - 0x1f4];
    void (*onLand)(Actor *actor, int frame);
    u8 pad_200[0x228 - 0x200];
    BOOL (*getTarget)(Actor *actor, VecFx32 *out);
    u8 pad_22c[0x234 - 0x22c];
    u32 stateFlags;
    u8 pad_238[0x760 - 0x238];
    s32 frame;
    u8 pad_764[4];
    s32 active;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 player;
    u8 pad_9b5[0x9c8 - 0x9b5];
    VecFx32 pos;
    u8 pad_9d4[0xa51 - 0x9d4];
    s8 animIndex;
    u8 pad_a52[0xb2c - 0xa52];
    u8 sound[0x1078 - 0xb2c];
    SceneObject *obj;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setMode)(Actor *actor, int mode);
};

extern const s16 data_02053580[];

extern InputEntry *GetPlayerControlState(int player);
extern int func_ov001_02072040(void);
extern BOOL UpdateIdleTimeout(void);
extern u16 SharedObject_GetId(void *self);
extern s32 SharedObject_GetMode(void *obj);
extern void CameraPath_Start(void *path);
extern void RestartScriptSound(void *sound, int arg);
extern void SetSlotEntryValue(int groupId, int slot, int value);
extern void ActivateSlotModelGroup(Actor *actor, int index);
extern VecFx32 *func_ov052_020ceb74(Actor *actor);
extern void Handle_WritePayloadIfLive(u32 handle, VecFx32 *src);
extern void StopSoundSeqHandle(u32 handle);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern BOOL IsGroupMemberActive(int groupId, int index);
extern void StopAndClearSoundEmitter(int groupId, int index);
extern void ScaleVecFx32(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern int FX_Mul(int left, int right);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void func_ov052_020cfdd4(Actor *actor, AnimEntry *entry, int arg);
extern void ApplyAnimRootMotion(Actor *actor, AnimEntry *entry);
extern void InitSlotEntryFromRecord(SlotEntry *entry, void *source, int mirrored, SceneObject *record, int player);
extern int ProcessTargetHitEntries(Actor *actor, AnimEntry *target, SlotEntry *entry);
extern BOOL UpdateActionPhase(Actor *actor, AnimEntry *data, int which);
extern BOOL HandlePendingCommand(Actor *actor);
extern void AimOv069BossAtHit();

static inline int PlayActorSound(Actor *actor, int id)
{
    int (*play)(Actor *actor, int id, int a, int b) = actor->playSound;

    if (play != NULL) {
        return play(actor, id, 0, 0);
    }
    return -1;
}

void UpdateOv069BossMotion(Actor *actor)
{
    SceneObject *obj = actor->obj;
    InputEntry *input;
    int group;
    MarkerRequest request;
    VecFx32 vel;
    VecFx32 target;
    VecFx32 dir;
    SlotEntry slot;
    AnimEntry *entries;
    int index;
    BOOL found;
    int frame;
    u16 heading;
    int angle;
    u32 grounded;

    input = GetPlayerControlState(actor->player);
    group = obj->group;
    switch (obj->counter.count) {
    default:
        obj->counter.count = 0;
        break;
    case 0:
        break;
    case 1:
        obj->counter.count = 2;
    case 2:
        if (func_ov001_02072040() && !UpdateIdleTimeout()) {
            if (SharedObject_GetId(input) == 5) {
                switch (SharedObject_GetMode(input)) {
                case 1:
                case 3:
                    obj->speed = 0xa00;
                    obj->counter.mode = 2;
                    input->field12 = 0;
                    break;
                case 4:
                    obj->counter.mode = 3;
                    CameraPath_Start(obj->cameraPath);
                    RestartScriptSound(actor->sound, 0);
                    obj->counter.count = 3;
                    if (obj->slot != -1) {
                        SetSlotEntryValue(group, obj->slot, 0);
                    }
                    obj->counter.step = 4;
                    break;
                }
            }
            if (obj->counter.count == 2) {
                frame = actor->frame;
                if (frame >= 0x12000) {
                    int landFrame = frame - 0x4000;
                    s8 savedSlot = obj->slot;

                    ActivateSlotModelGroup(actor, actor->animIndex);
                    if (actor->onLand != NULL) {
                        actor->onLand(actor, landFrame);
                    }
                    obj->slot = savedSlot;
                }
            }
        } else if (actor->frame >= 0x12000) {
            if (obj->slot != -1) {
                SetSlotEntryValue(group, obj->slot, 0);
            }
            obj->counter.step = 3;
            actor->animIndex = 1;
            ActivateSlotModelGroup(actor, actor->animIndex);
            obj->counter.count = 3;
        }
        break;
    case 3:
        obj->counter.count = 0;
        break;
    }
    switch (obj->counter.step) {
    default:
        obj->counter.step = 0;
    case 0:
        if (obj->seqHandle != -1) {
            Handle_WritePayloadIfLive(obj->seqHandle, func_ov052_020ceb74(actor));
        }
        break;
    case 1:
        if (actor->frame >= 0x7000) {
            ResetAnimationTrackState(&request);
            request.id = actor->player;
            request.layer = 1;
            request.angle = 0x8000;
            request.hidden = 0;
            obj->slot = func_ov021_020a8cc0(&request, group);
            obj->seqHandle = PlayActorSound(actor, obj->soundId);
            obj->counter.step = 2;
        }
        break;
    case 2:
        if (actor->frame >= 0xd000) {
            ResetAnimationTrackState(&request);
            request.id = actor->player;
            request.layer = 1;
            request.flags = 4;
            request.angle = 0x8000;
            request.hidden = 1;
            if (obj->slot != -1) {
                StopAndClearSoundEmitter(group, obj->slot);
            }
            obj->slot = func_ov021_020a8cc0(&request, group);
            obj->counter.step = 0;
        }
        break;
    case 3:
    case 4:
        if (obj->slot == -1 || !IsGroupMemberActive(group, obj->slot)) {
            ResetAnimationTrackState(&request);
            request.id = actor->player;
            request.layer = 1;
            request.angle = 0x8000;
            switch (obj->counter.step) {
            case 4:
                request.hidden = 3;
                request.soundId = obj->soundId;
                request.delay = 2;
                break;
            case 3:
                request.hidden = 2;
                request.soundId = obj->soundId;
                request.delay = 1;
                break;
            }
            if (obj->seqHandle != -1) {
                StopSoundSeqHandle(obj->seqHandle);
                obj->seqHandle = -1;
            }
            if (obj->slot != -1) {
                StopAndClearSoundEmitter(group, obj->slot);
            }
            obj->slot = func_ov021_020a8cc0(&request, group);
            obj->counter.step = 0;
        }
        break;
    }
    switch (obj->counter.mode) {
    default:
        obj->counter.mode = 0;
        break;
    case 0:
    case 4:
        break;
    case 1:
        ScaleVecFx32(obj->speed, &obj->dir, &vel);
        actor->pos.x += vel.x;
        actor->pos.z += vel.z;
        if (vel.y > 0) {
            actor->pos.y = vel.y;
        }
        obj->speed = FX_Mul(obj->speed, 0xa00);
        if (obj->speed >= 0x100) {
            break;
        }
        obj->speed = 0;
    reset:
        obj->counter.mode = 0;
        break;
    case 2:
    case 3:
        if (actor->getTarget != NULL) {
            found = actor->getTarget(actor, &target);
        } else {
            found = FALSE;
        }
        if (found) {
            VEC_Subtract(&target, &actor->center, &dir);
            if (VEC_DotProduct(&dir, &dir) > 4) {
                VEC_Normalize(&dir, &dir);
                goto scale;
            }
        }
        heading = actor->angle - 0x8000;
        angle = (u16)(heading + 0x8000) >> 4;
        dir.x = data_02053580[angle];
        dir.y = 0;
        dir.z = data_02053580[(0x400 - angle) & 0xfff];
    scale:
        ScaleVecFx32(obj->speed, &dir, &dir);
        actor->pos.x += dir.x;
        actor->pos.z += dir.z;
        actor->pos.y = dir.y;
        obj->speed = FX_Mul(obj->speed, 0xd00);
        if (obj->speed >= 0x100) {
            break;
        }
        obj->speed = 0;
        switch (obj->counter.mode) {
        default:
            obj->counter.mode = 0;
            break;
        case 3:
            obj->counter.mode = 4;
            break;
        }
        break;
    }
    entries = obj->entries;
    index = actor->animIndex;
    func_ov052_020cfdd4(actor, &entries[index], 1);
    ApplyAnimRootMotion(actor, &entries[index]);
    InitSlotEntryFromRecord(&slot, &entries[index], 1, obj, actor->player);
    slot.callback = AimOv069BossAtHit;
    slot.context = obj;
    slot.hitOnce = 1;
    slot.mirrored = 0;
    if (ProcessTargetHitEntries(actor, &entries[index], &slot)) {
        return;
    }
    if (UpdateActionPhase(actor, &entries[index], 1)) {
        return;
    }
    if (actor->active == 0) {
        return;
    }
    grounded = actor->stateFlags & 4;
    if (HandlePendingCommand(actor)) {
        return;
    }
    if (grounded) {
        actor->setMode(actor, 5);
        return;
    }
    actor->setMode(actor, 4);
}
