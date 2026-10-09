#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct EventTargetInfo {
    u16 id;
    u16 flags;
    u16 kind;
    u16 pad_06;
    VecFx32 position;
    s32 width;
    s32 height;
    s32 displayWidth;
    s32 displayHeight;
} EventTargetInfo;

typedef struct EffectRequest {
    u8 layer;
    u8 pad_01[3];
    VecFx32 position;
    u8 pad_10[0x14];
    u8 flagA;
    u8 flagB;
    u8 pad_26[6];
} EffectRequest;

typedef struct ProjectileDesc {
    u32 kind;
    u8 pad_04[0xc];
    u8 mode;
    u8 pad_11[3];
    fx32 offsetX;
    fx32 offsetY;
    fx32 offsetZ;
    u8 pad_20[4];
    u16 flags;
    u8 pad_26[2];
} ProjectileDesc;

typedef struct ProjectileSpawn {
    u8 data[0x28];
} ProjectileSpawn;

typedef struct CutsceneWork {
    s32 state;
    s32 timer;
    u8 pad_08[8];
    s32 burstStarted;
    u8 pad_14[4];
    s32 targetId;
    s32 sparkCount;
    u8 pad_20[0x18];
    s16 sparkGroup;
    s16 burstGroup;
} CutsceneWork;

typedef struct Controller Controller;
typedef void (*FaceFunc)(Controller *self, int angle);
typedef void (*SpeedFunc)(Controller *self, int speed);
typedef void (*SoundFunc)(Controller *self, int id, int arg, int extra);
typedef void (*EndFunc)(Controller *self, int arg, int extra);
typedef void (*EnableFunc)(Controller *self, int enable);

struct Controller {
    u8 pad_000[0x1f0];
    SoundFunc playSound;
    u8 pad_1f4[4];
    EndFunc finish;
    SpeedFunc setSpeed;
    u8 pad_200[0x10];
    FaceFunc setFacing;
    u8 pad_214[0x760 - 0x214];
    s32 frame;
    u8 pad_764[4];
    s32 done;
    u8 pad_76c[0x9ac - 0x76c];
    u64 stateFlags;
    u8 layer;
    u8 pad_9b5[0x9c8 - 0x9b5];
    VecFx32 cameraPos;
    u8 pad_9d4[0xb58 - 0x9d4];
    s32 voiceId;
    u8 pad_b5c[0x1048 - 0xb5c];
    u8 hasTarget;
    u8 pad_1049[3];
    s16 targetId;
    u8 pad_104e[0x10ec - 0x104e];
    EnableFunc setEnabled;
};

extern CutsceneWork *data_ov010_020a1dc0;

extern void func_ov052_020ce9d4(Controller *self, VecFx32 *out);
extern VecFx32 *func_ov052_020ceb54(Controller *self);
extern void func_ov052_020ceb60(Controller *self, VecFx32 *pos);
extern BOOL GetStageEventTargetInfo_02087960(int id, EventTargetInfo *info);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9f88(const VecFx32 *src, VecFx32 *dst);
extern void VEC_MultAdd_01ffa09c(fx32 scale, const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern u16 FixedPointAtan2_020062bc(fx32 y, fx32 x);
extern fx32 FixedPointMultiply12(fx32 a, fx32 b);
extern fx32 nextRandom12_0202aa58(void);
extern void func_ov021_020a8ab4(EffectRequest *request);
extern int func_ov021_020a8ca0(EffectRequest *request, int groupId);
extern void ZeroBytes0x28_020ac0f8(ProjectileDesc *desc);
extern void func_ov021_020ac104(ProjectileSpawn *out, int targetId, int slot, int flags, VecFx32 *origin, fx32 *offset);
extern void func_ov021_020ac33c(ProjectileDesc *desc, ProjectileSpawn *spawn);
extern void func_ov001_020645e8(int eventId);
extern void func_ov010_020a0d00(CutsceneWork *work);
extern void func_ov010_020a1028(CutsceneWork *work);

static inline void SetVec(VecFx32 *vec, fx32 x, fx32 y, fx32 z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

static inline void Controller_FaceDirection(Controller *self, const VecFx32 *dir)
{
    BOOL nonZero = dir->x != 0 || dir->y != 0 || dir->z != 0;
    if (nonZero) {
        u16 angle = FixedPointAtan2_020062bc(dir->x, dir->z) + 0x8000;
        if (self->setFacing != NULL) {
            self->setFacing(self, angle);
        }
    }
}

static inline void Controller_PlaySound(Controller *self, int id, int arg)
{
    if (self->playSound != NULL) {
        self->playSound(self, id, arg, 0);
    }
}

void Entity_UpdateSpecialStrike_020a13cc(Controller *self)
{
    CutsceneWork *work = data_ov010_020a1dc0;
    EffectRequest request;
    EventTargetInfo info;
    VecFx32 camera;
    VecFx32 delta;
    VecFx32 dest;
    ProjectileDesc desc;
    ProjectileSpawn spawn;

    func_ov052_020ce9d4(self, &camera);
    SetVec(&self->cameraPos, camera.x, camera.y, camera.z);

    if (work->targetId >= 0 && !GetStageEventTargetInfo_02087960((u16)work->targetId, &info)) {
        work->targetId = -1;
    }
    work->timer += 0x1000;

    switch (work->state) {
    case 3:
        if (work->targetId >= 0) {
            VEC_Subtract_01ff9e3c(&info.position, func_ov052_020ceb54(self), &delta);
            Controller_FaceDirection(self, &delta);
        }
        if (work->burstStarted == 0 && self->frame >= 0xa000) {
            work->burstStarted = 1;
            func_ov021_020a8ab4(&request);
            request.layer = self->layer;
            request.flagB = 0;
            request.flagA = 0;
            request.position = *func_ov052_020ceb54(self);
            func_ov021_020a8ca0(&request, work->burstGroup);
        }
        if (self->frame >= 0xd000) {
            if (work->targetId >= 0) {
                VEC_Subtract_01ff9e3c(func_ov052_020ceb54(self), &info.position, &delta);
                if (delta.x != 0 || delta.y != 0 || delta.z != 0) {
                    func_01ff9f88(&delta, &delta);
                    VEC_MultAdd_01ffa09c(0x1333, &delta, &info.position, &dest);
                    dest.y = 0;
                    func_ov052_020ceb60(self, &dest);
                }
            }
            work->state = 4;
            work->timer = 0;
            return;
        }
        break;
    case 4:
        if (work->sparkCount < 3) {
            if (self->frame >= 0x15000) {
                if (self->setSpeed != NULL) {
                    self->setSpeed(self, 0xe000);
                }
                work->sparkCount++;
            }
            if (work->timer % 0x3000 == 0) {
                func_ov021_020a8ab4(&request);
                request.layer = self->layer;
                request.flagB = 0;
                request.flagA = 0;
                request.position = info.position;
                request.position.x += FixedPointMultiply12(nextRandom12_0202aa58() - 0x800, 0x1800);
                request.position.y += FixedPointMultiply12(nextRandom12_0202aa58() - 0x800, 0x1800);
                request.position.z += FixedPointMultiply12(nextRandom12_0202aa58() - 0x800, 0x1800);
                request.position.y += 0x800;
                func_ov021_020a8ca0(&request, work->sparkGroup);
                return;
            }
        } else if (self->frame > 0x15000) {
            work->targetId = -1;
            if (self->hasTarget == 1) {
                work->targetId = self->targetId;
            }
            if (work->targetId >= 0) {
                ZeroBytes0x28_020ac0f8(&desc);
                desc.kind = 0x17ae;
                desc.flags |= 0x80;
                desc.mode = 0;
                desc.flags = (desc.flags & ~1) | 1;
                desc.offsetY = 0x2800;
                desc.offsetX = 0;
                desc.offsetZ = 0;
                func_ov021_020ac104(&spawn, work->targetId, ~0, 0, func_ov052_020ceb54(self), &desc.offsetX);
                func_ov021_020ac33c(&desc, &spawn);
                Controller_PlaySound(self, 0xf4, 0x1c);
                Controller_PlaySound(self, self->voiceId, 5);
            }
            func_ov010_020a1028(work);
            work->state = 5;
            work->timer = 0;
            return;
        }
        break;
    case 5:
        if (self->done != 0) {
            func_ov010_020a0d00(work);
            func_ov001_020645e8(0x3717);
            self->stateFlags &= ~(u64)0x01000000;
            self->setEnabled(self, 1);
            if (self->finish != NULL) {
                self->finish(self, 0, -1);
            }
        }
        break;
    }
}
