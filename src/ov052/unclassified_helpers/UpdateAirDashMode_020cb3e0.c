#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Actor Actor;
typedef void (*ExitFunc)(Actor *actor, int arg, int value);
typedef void (*SetModeFunc)(Actor *actor, int mode);

struct Actor {
    u8 pad_0000[0x1f8];
    ExitFunc onModeExit;
    u8 pad_01fc[0x234 - 0x1fc];
    u32 flags;
    u8 pad_0238[0x75c - 0x238];
    int mode;
    u8 pad_0760[0x9ac - 0x760];
    u64 stateFlags;
    u8 player;
    u8 pad_09b5[0x9c4 - 0x9b5];
    int chargeTime;
    VecFx32 velocity;
    u8 pad_09d4[0xa10 - 0x9d4];
    u8 speed[0x3f];
    s8 comboLevel;
    u8 pad_0a50[0x10ec - 0xa50];
    SetModeFunc setMode;
    u8 pad_10f0[0x1108 - 0x10f0];
    u8 marker[4];
};

extern s16 data_0205356c[];
extern void *func_ov001_0206db78(int player);
extern void func_ov052_020d12f0(Actor *actor, int enable);
extern void ActivateSlotMarker_020ab7cc(void *marker);
extern int ApproachTargetValue_020d0e80(void *value);
extern u16 GetLinkedAngleOffset_020ceb7c(Actor *actor);
extern int FixedPointMultiply12(int left, int right);
extern BOOL AlarmCallback_020a7504(void *input);
extern BOOL HasFlagsAt0xe_020a752c(void *input, u16 mask);
extern BOOL IsPlayerEntryFlagSet_02050014(int player, u32 id);

void UpdateAirDashMode_020cb3e0(Actor *actor)
{
    void *input = func_ov001_0206db78(actor->player);
    u32 flagSet = actor->flags & 4;
    fx32 speed;
    int index;
    fx32 dx;
    fx32 dz;
    fx32 lift;
    int i;
    int count;
    BOOL glide;

    if (actor->mode != 0x10) {
        if (actor->onModeExit != NULL) {
            actor->onModeExit(actor, 0x10, -1);
        }
        func_ov052_020d12f0(actor, 1);
    }
    if (actor->chargeTime == 0x2000 && !(actor->stateFlags & 0x100000020ULL)) {
        ActivateSlotMarker_020ab7cc(actor->marker);
    }
    speed = ApproachTargetValue_020d0e80(actor->speed);
    index = GetLinkedAngleOffset_020ceb7c(actor) >> 4;
    dx = FixedPointMultiply12(-data_0205356c[index], speed);
    dz = FixedPointMultiply12(-data_0205356c[(0x400 - index) & 0xfff], speed);
    lift = 0x1000;
    i = 0;
    count = actor->comboLevel - 1;
    for (; i < count; i++) {
        lift = lift * 3 / 4;
    }
    lift = FixedPointMultiply12(0x80, lift);
    if (!flagSet) {
        actor->velocity.y = lift;
        actor->velocity.x += dx;
        actor->velocity.z += dz;
    }
    if (!flagSet && actor->chargeTime < 0x6000) {
        return;
    }
    if (!flagSet) {
        glide = FALSE;
        if (AlarmCallback_020a7504(input) && HasFlagsAt0xe_020a752c(input, 0x800)
            && IsPlayerEntryFlagSet_02050014(actor->player, 0xe) && !(actor->stateFlags & 0x8000)) {
            glide = TRUE;
        }
        if (glide) {
            actor->setMode(actor, 0x11);
            return;
        }
        actor->setMode(actor, 4);
        return;
    }
    actor->setMode(actor, 5);
}
