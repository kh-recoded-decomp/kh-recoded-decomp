#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 id;
    u8 pad_01[3];
    fx32 scaleA;
    fx32 scaleB;
    u8 pad_0c[0x10];
    fx32 sizeA;
    fx32 sizeB;
    u8 hidden;
    u8 layer;
    u16 flags;
    u8 pad_28[4];
} MarkerRequest;

typedef struct {
    u8 pad_00[0x40];
    u8 phase;
    u8 pad_41[3];
    int progress;
    u8 pad_48[4];
    int field4c;
    s16 loopEmitter;
    u8 pad_52[6];
    int loopHandle;
    BOOL loopStarted;
} BossObject;

typedef struct {
    u32 pad_00;
    u16 anim[2];
} BodyModel;

typedef struct Actor Actor;
struct Actor {
    u8 pad_000[0x1fc];
    void (*onLand)(Actor *actor, int frame);
    u8 pad_200[4];
    void (*onSignal)(Actor *actor, int signal);
    u8 pad_208[8];
    void (*onTurn)(Actor *actor, u16 angle);
    u8 pad_214[0x230 - 0x214];
    BodyModel *body;
    u32 modeFlags;
    u8 pad_238[0x768 - 0x238];
    BOOL finished;
    u8 pad_76c[0x9b4 - 0x76c];
    u8 player;
    u8 pad_9b5[0x9c8 - 0x9b5];
    fx32 posX;
    fx32 posY;
    fx32 posZ;
    u8 pad_9d4[0x1078 - 0x9d4];
    BossObject *boss;
    u8 pad_107c[0x10ec - 0x107c];
    void (*setMode)(Actor *actor, int mode);
};

extern void ComputeRootMotionDelta(Actor *actor, VecFx32 *out);
extern int GetOv070PaletteEntry(BossObject *boss);
extern BOOL func_ov001_0207d52c(int slot, u32 value);
extern int Anim_GetFrame(void *anim, int arg);
extern int func_0202f4cc(void *anim, int arg);
extern void Camera_SetFollowDistance(fx32 distance);
extern void Camera_BlendToPlayerBackView(s32 curveType, fx32 duration);
extern void ResetAnimationTrackState(MarkerRequest *request);
extern int func_ov021_020a8cc0(MarkerRequest *request, int groupId);
extern void *GetGroupMemberData(int groupId, int index);
extern void StopAndClearSoundEmitter(int emitter, int handle);
extern int func_ov046_020c0d88(void);
extern BOOL UpdateIdleTimeout(void);
extern VecFx32 *GetCameraViewUpVector(void);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern u16 FX_Atan2Idx(int y, int x);
extern void Camera_ChangeModeFromCurrentView(s32 mode);
extern void ResetGaugeDisplay(void);
extern void SetManagerEnabled(u32 enabled);

void UpdateOv070BossTurnState(Actor *actor)
{
    BossObject *boss = actor->boss;
    MarkerRequest request;
    VecFx32 delta;
    VecFx32 dir;
    void *anim;
    int frame;
    int remaining;
    u32 grounded;
    u16 angle;

    ComputeRootMotionDelta(actor, &delta);
    actor->posY = delta.y;
    actor->posX += delta.x;
    actor->posZ += delta.z;
    remaining = GetOv070PaletteEntry(boss) - boss->progress;
    if (remaining < 0) {
        remaining = 0;
    }
    func_ov001_0207d52c(1, remaining / 30 + 0xfff);
    switch (boss->phase) {
    case 0:
        if (Anim_GetFrame(actor->body->anim, 0) < 0xc000) {
            return; /* early return keeps the long branch */
        }
        Camera_SetFollowDistance(-0x59a);
        Camera_BlendToPlayerBackView(3, 0x8000);
        boss->loopStarted = FALSE;
        ResetAnimationTrackState(&request);
        request.id = actor->player;
        request.flags |= 0x20;
        request.layer = 3;
        request.scaleA = 0x80000;
        request.scaleB = 0x64000;
        request.sizeA = 0x20800;
        request.sizeB = 0x20800;
        request.hidden = 0;
        boss->loopHandle = func_ov021_020a8cc0(&request, boss->loopEmitter);
        boss->field4c = 0;
        boss->phase = 1;
        break;
    case 1:
        if (!boss->loopStarted) {
            anim = GetGroupMemberData(boss->loopEmitter, boss->loopHandle);
            frame = Anim_GetFrame(anim, 0);
            if (frame >= func_0202f4cc(anim, 0) - 0x1000) {
                StopAndClearSoundEmitter(boss->loopEmitter, boss->loopHandle);
                boss->loopHandle = -1;
                ResetAnimationTrackState(&request);
                request.id = actor->player;
                request.flags |= 0x24;
                request.layer = 3;
                request.scaleA = 0x80000;
                request.scaleB = 0x64000;
                request.sizeA = 0x20800;
                request.hidden = 1;
                request.sizeB = 0x20800;
                boss->loopHandle = func_ov021_020a8cc0(&request, boss->loopEmitter);
                boss->loopStarted = TRUE;
            }
        }
        if (func_ov046_020c0d88() != 2) {
            if (actor->onSignal != NULL) {
                actor->onSignal(actor, 0);
            }
            boss->phase = 2;
        }
        break;
    case 2:
        if (Anim_GetFrame(actor->body->anim, 0) > 0x1a000 && actor->onLand != NULL) {
            actor->onLand(actor, 0xc000);
        }
        if (boss->progress >= GetOv070PaletteEntry(boss) || UpdateIdleTimeout()) {
            if (actor->onLand != NULL) {
                actor->onLand(actor, 0x1b000);
            }
            StopAndClearSoundEmitter(boss->loopEmitter, boss->loopHandle);
            boss->loopHandle = -1;
            ResetAnimationTrackState(&request);
            request.id = actor->player;
            request.flags |= 0x20;
            request.layer = 3;
            request.scaleA = 0x80000;
            request.scaleB = 0x64000;
            request.sizeA = 0x20800;
            request.sizeB = 0x20800;
            request.hidden = 2;
            func_ov021_020a8cc0(&request, boss->loopEmitter);
            dir = *GetCameraViewUpVector();
            dir.y = 0;
            VEC_Normalize(&dir, &dir);
            angle = FX_Atan2Idx(dir.x, dir.z) + 0x7fff;
            if (actor->onTurn != NULL) {
                actor->onTurn(actor, angle);
            }
            if (actor->onSignal != NULL) {
                actor->onSignal(actor, 0x1f);
            }
            Camera_ChangeModeFromCurrentView(0);
            boss->phase = 3;
        }
        break;
    case 3:
        if (actor->finished) {
            grounded = actor->modeFlags & 4;
            ResetGaugeDisplay();
            SetManagerEnabled(0);
            if (grounded) {
                actor->setMode(actor, 5);
            } else {
                actor->setMode(actor, 4);
            }
            boss->phase = 0;
        }
        break;
    }
}
