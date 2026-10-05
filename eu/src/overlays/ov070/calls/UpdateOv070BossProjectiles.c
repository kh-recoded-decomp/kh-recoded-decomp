#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s32 minX, minY, minZ;
    s32 maxX, maxY, maxZ;
} Box;

typedef struct {
    u32 kind;
    Box box;
    int index;
    VecFx32 delta;
    Box sweptBox;
} HitVolume;

typedef struct {
    HitVolume volume;
    u32 owner;
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
    u8 pad_12[2];
    VecFx32 push;
    int pushDelay;
    volatile u16 flags;
    u8 pad_26[2];
} HitOptions;

typedef struct {
    u8 pad_00[8];
    s32 kind;
    u8 pad_0c[0xc];
    u16 eventId;
    u8 pad_1a[0xdc - 0x1a];
} HitScan;

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
    u8 pad_00[0xa4];
    VecFx32 position;
} GroupMember;

typedef struct BossEntity BossEntity;
struct BossEntity {
    u8 pad_000[0x204];
    void (*setAlpha)(BossEntity *entity, u8 alpha);
    u8 pad_208[0x9b4 - 0x208];
    u8 player;
};

typedef struct {
    u8 pad_00[0x14];
    int player;
} SceneOwner;

typedef struct {
    int active;
    int timer;
    int handle;
    VecFx32 position;
    VecFx32 velocity;
} EffectSlot;

typedef struct {
    u8 pad_00[8];
    int sound;
    u8 pad_0c[0x34];
    u8 phase;
    u8 pad_41[3];
    int elapsed;
    int busy;
    int fade;
    s16 loopEmitter;
    s16 slotEmitter;
    s16 burstEmitter;
    u8 pad_56[0xa];
    EffectSlot slots[10];
} SceneObject;

extern u16 data_02060500;

extern BossEntity *GetBoundedEntryField(int index);
extern u16 GetLinkedAngleOffset(BossEntity *entity);
extern VecFx32 *func_ov052_020ceb74(BossEntity *entity);
extern VecFx32 *GetCameraViewUpVector(void);
extern void func_01ffafb4(fx32 scale, const VecFx32 *src, VecFx32 *dst);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern GroupMember *GetGroupMemberData(int groupId, int index);
extern void StopAndClearSoundEmitter(int emitter, int handle);
extern void PlaySoundChecked(int sound, int arg);
extern void InitRecord60(HitAttack *attack);
extern void func_0203ad28(HitVolume *volume, int *bounds, const VecFx32 *center, fx32 radius);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern void ZeroBytes0x28(void *obj);
extern void ZeroAndSetField0xd4(void *obj);
extern BOOL StepHitScan(int type, HitAttack *attack, HitOptions *options, HitScan *scan);
extern void UpdateStageEventMessage(u16 eventId);
extern BOOL func_ov070_020d8120(SceneObject *obj);

void UpdateOv070BossProjectiles(SceneOwner *owner, SceneObject *obj, fx32 delta)
{
    HitScan scan;
    HitAttack attack;
    HitVolume volume;
    VecFx32 step;
    MarkerRequest request;
    int bounds[4];
    HitOptions options;
    VecFx32 dir;
    BossEntity *entity;
    EffectSlot *slot;
    GroupMember *member;
    HitScan *scanPtr;
    BOOL hit;
    int alpha;
    int i;

    entity = GetBoundedEntryField(owner->player);
    if (obj->phase >= 2) {
        obj->elapsed += delta;
    }
    if (obj->phase == 1) {
        obj->fade += delta;
        if (obj->fade >= 0x8000) {
            obj->fade = 0x8000;
        }
        alpha = 31.0f * (1.0f - (float)obj->fade / 4096.0f / 8.0f);
        if (entity->setAlpha != NULL) {
            entity->setAlpha(entity, alpha);
        }
    }
    if (obj->phase == 2 && (data_02060500 & 1) && obj->busy == 0) {
        for (i = 0; i < 10; i++) {
            slot = &obj->slots[i];
            if (slot->active == 0) {
                slot->active = 1;
                slot->timer = 0;
                GetLinkedAngleOffset(entity);
                slot->position = *func_ov052_020ceb74(entity);
                slot->position.y += 0x1000;
                slot->velocity = *GetCameraViewUpVector();
                func_01ffafb4(0xd9a, &slot->velocity, &slot->velocity);
                ResetAnimationTrackState(&request);
                request.id = entity->player;
                request.layer = 0;
                request.hidden = 0;
                request.position = slot->position;
                request.flags |= 4;
                slot->handle = func_ov021_020a8cc0(&request, obj->slotEmitter);
                PlaySoundChecked(obj->sound, 0);
                break;
            }
        }
    }
    for (i = 0; i < 10; i++) {
        slot = &obj->slots[i];
        if (slot->active) {
            slot->timer += delta;
            func_01ffafb4(delta, &slot->velocity, &step);
            VEC_Add(&step, &slot->position, &slot->position);
            member = GetGroupMemberData(obj->slotEmitter, slot->handle);
            member->position = slot->position;
            hit = FALSE;
            InitRecord60(&attack);
            attack.motion = slot->velocity;
            func_0203ad28(&volume, bounds, &slot->position, 0x800);
            volume.delta = attack.motion;
            OffsetBoxByDelta(&volume.box, &volume.sweptBox, &volume.delta);
            attack.volume = volume;
            ZeroBytes0x28(&options);
            options.power = func_ov070_020d8120(obj) ? 0xb3f : 0x781;
            options.reaction = 1;
            options.reactionLevel = 1;
            VEC_Normalize(&slot->velocity, &dir);
            func_ov070_020d8120(obj);
            func_01ffafb4(0x333, &dir, &options.push);
            options.pushDelay = 0;
            options.flags |= 0x80;
            options.flags |= 0x800;
            scanPtr = &scan;
            ZeroAndSetField0xd4(scanPtr);
            while (StepHitScan(entity->player, &attack, &options, scanPtr)) {
                switch (scanPtr->kind) {
                case 1:
                case 2:
                case 3:
                    hit = TRUE;
                    break;
                case 4:
                    UpdateStageEventMessage(scanPtr->eventId);
                    hit = TRUE;
                    break;
                }
                if (hit == TRUE) {
                    break;
                }
            }
            if (slot->timer >= 0x1e000) {
                hit = TRUE;
            }
            if (hit == TRUE) {
                slot->active = 0;
                StopAndClearSoundEmitter(obj->slotEmitter, slot->handle);
                slot->handle = -1;
                ResetAnimationTrackState(&request);
                request.id = entity->player;
                request.layer = 0;
                request.hidden = 1;
                request.position = slot->position;
                request.soundId = obj->sound;
                request.delay = 1;
                func_ov021_020a8cc0(&request, obj->burstEmitter);
            }
        }
    }
}
