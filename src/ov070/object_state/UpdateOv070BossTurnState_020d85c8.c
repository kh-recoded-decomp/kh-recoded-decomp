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

extern void ComputeRootMotionDelta_020ce9d4(Actor *actor, VecFx32 *out);
extern int GetOv070PaletteEntry_020d8114(BossObject *boss);
extern BOOL SetPendingSlotFlagWithValue_0207d504(int slot, u32 value);
extern int Anim_GetFrame_0202f4a0(void *anim, int arg);
extern int func_0202f4b8(void *anim, int arg);
extern void Camera_SetFollowDistance_020c0dc4(fx32 distance);
extern void Camera_BlendToPlayerBackView_020c1360(s32 curveType, fx32 duration);
extern void func_ov021_020a8ab4(MarkerRequest *request);
extern int func_ov021_020a8ca0(MarkerRequest *request, int groupId);
extern void *GetGroupMemberData_020a8eec(int groupId, int index);
extern void StopAndClearSoundEmitter_020a8e14(int emitter, int handle);
extern int func_ov046_020c0d68(void);
extern BOOL UpdateIdleTimeout_0206e1c8(void);
extern VecFx32 *func_ov048_020c384c(void);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern u16 FixedPointAtan2_020062bc(int y, int x);
extern void Camera_ChangeModeFromCurrentView_020c1014(s32 mode);
extern void ResetGaugeDisplay_020734f8(void);
extern void SetManagerEnabled_0206e160(u32 enabled);

void UpdateOv070BossTurnState_020d85c8(Actor *actor)
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

    ComputeRootMotionDelta_020ce9d4(actor, &delta);
    actor->posY = delta.y;
    actor->posX += delta.x;
    actor->posZ += delta.z;
    remaining = GetOv070PaletteEntry_020d8114(boss) - boss->progress;
    if (remaining < 0) {
        remaining = 0;
    }
    SetPendingSlotFlagWithValue_0207d504(1, remaining / 30 + 0xfff);
    switch (boss->phase) {
    case 0:
        if (Anim_GetFrame_0202f4a0(actor->body->anim, 0) < 0xc000) {
            return; /* early return keeps the long branch */
        }
        Camera_SetFollowDistance_020c0dc4(-0x59a);
        Camera_BlendToPlayerBackView_020c1360(3, 0x8000);
        boss->loopStarted = FALSE;
        func_ov021_020a8ab4(&request);
        request.id = actor->player;
        request.flags |= 0x20;
        request.layer = 3;
        request.scaleA = 0x80000;
        request.scaleB = 0x64000;
        request.sizeA = 0x20800;
        request.sizeB = 0x20800;
        request.hidden = 0;
        boss->loopHandle = func_ov021_020a8ca0(&request, boss->loopEmitter);
        boss->field4c = 0;
        boss->phase = 1;
        break;
    case 1:
        if (!boss->loopStarted) {
            anim = GetGroupMemberData_020a8eec(boss->loopEmitter, boss->loopHandle);
            frame = Anim_GetFrame_0202f4a0(anim, 0);
            if (frame >= func_0202f4b8(anim, 0) - 0x1000) {
                StopAndClearSoundEmitter_020a8e14(boss->loopEmitter, boss->loopHandle);
                boss->loopHandle = -1;
                func_ov021_020a8ab4(&request);
                request.id = actor->player;
                request.flags |= 0x24;
                request.layer = 3;
                request.scaleA = 0x80000;
                request.scaleB = 0x64000;
                request.sizeA = 0x20800;
                request.hidden = 1;
                request.sizeB = 0x20800;
                boss->loopHandle = func_ov021_020a8ca0(&request, boss->loopEmitter);
                boss->loopStarted = TRUE;
            }
        }
        if (func_ov046_020c0d68() != 2) {
            if (actor->onSignal != NULL) {
                actor->onSignal(actor, 0);
            }
            boss->phase = 2;
        }
        break;
    case 2:
        if (Anim_GetFrame_0202f4a0(actor->body->anim, 0) > 0x1a000 && actor->onLand != NULL) {
            actor->onLand(actor, 0xc000);
        }
        if (boss->progress >= GetOv070PaletteEntry_020d8114(boss) || UpdateIdleTimeout_0206e1c8()) {
            if (actor->onLand != NULL) {
                actor->onLand(actor, 0x1b000);
            }
            StopAndClearSoundEmitter_020a8e14(boss->loopEmitter, boss->loopHandle);
            boss->loopHandle = -1;
            func_ov021_020a8ab4(&request);
            request.id = actor->player;
            request.flags |= 0x20;
            request.layer = 3;
            request.scaleA = 0x80000;
            request.scaleB = 0x64000;
            request.sizeA = 0x20800;
            request.sizeB = 0x20800;
            request.hidden = 2;
            func_ov021_020a8ca0(&request, boss->loopEmitter);
            dir = *func_ov048_020c384c();
            dir.y = 0;
            func_01ff9f88(&dir, &dir);
            angle = FixedPointAtan2_020062bc(dir.x, dir.z) + 0x7fff;
            if (actor->onTurn != NULL) {
                actor->onTurn(actor, angle);
            }
            if (actor->onSignal != NULL) {
                actor->onSignal(actor, 0x1f);
            }
            Camera_ChangeModeFromCurrentView_020c1014(0);
            boss->phase = 3;
        }
        break;
    case 3:
        if (actor->finished) {
            grounded = actor->modeFlags & 4;
            ResetGaugeDisplay_020734f8();
            SetManagerEnabled_0206e160(0);
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
