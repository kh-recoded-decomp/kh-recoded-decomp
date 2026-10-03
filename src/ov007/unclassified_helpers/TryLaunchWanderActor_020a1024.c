#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 active : 1;
    u8 airborne : 1;
    u8 flagsHigh : 6;
    u8 phase;
    u16 timer;
    VecFx32 origin;
    VecFx32 velocity;
    fx32 scale;
    fx32 elapsed;
} LaunchMotion;

typedef struct {
    u8 pad_00[0x4e];
    u16 drawFlags;
    u8 pad_50[0x8];
    VecFx32 position;
    LaunchMotion motion[2];
    s16 heading;
    u8 facing;
    s8 state;
} WanderActor;

typedef struct {
    u8 pad_00[0x20];
    u32 flags;
} FieldState;

extern FieldState *data_ov001_020a0460;
extern VecFx32 data_02053438;
extern BOOL func_ov001_02063620(void);
extern BOOL func_ov001_02064490(void);
extern VecFx32 *func_ov007_020a0fec(WanderActor *actor);
extern int GetBoundedEntryField_0206db5c(int index);
extern BOOL func_ov040_020be02c(int entry, int *heading, u32 *facing);
extern VecFx32 *func_ov001_0206dc60(int index);
extern void StartLaunchMotion_020a0e58(WanderActor *actor, VecFx32 *velocity);
extern void PlaySoundChecked_0204d8d0(int channel, int soundId);

BOOL TryLaunchWanderActor_020a1024(WanderActor *actor) {
    LaunchMotion *motion;
    int player;
    int heading;
    u32 facing;

    if (actor->state != 0) {
        return FALSE;
    }
    if (func_ov001_02063620() || (data_ov001_020a0460->flags & 0x10) || func_ov001_02064490()) {
        return FALSE;
    }
    heading = actor->heading;
    facing = actor->facing;
    actor->position = *func_ov007_020a0fec(actor);
    player = 0;
    if (func_ov040_020be02c(GetBoundedEntryField_0206db5c(0), &heading, &facing)) {
        actor->heading = heading;
        actor->facing = facing;
        StartLaunchMotion_020a0e58(actor, func_ov001_0206dc60(player));
    } else {
        actor->state = 2;
    }
    motion = &actor->motion[0];
    actor->motion[0].active = TRUE;
    actor->motion[0].airborne = TRUE;
    motion->timer = 0;
    motion->velocity = data_02053438;
    actor->drawFlags &= ~0x10;
    PlaySoundChecked_0204d8d0(0, 0x3a);
    return FALSE;
}
