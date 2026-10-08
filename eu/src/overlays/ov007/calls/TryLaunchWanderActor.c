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

extern FieldState *data_ov001_020a0480;
extern VecFx32 data_0205344c;
extern BOOL func_ov001_02063620(void);
extern BOOL func_ov001_02064490(void);
extern VecFx32 *func_ov007_020a100c(WanderActor *actor);
extern int GetBoundedEntryField(int index);
extern BOOL GrantRewardItem(int entry, int *heading, u32 *facing);
extern VecFx32 *func_ov001_0206dc60(int index);
extern void StartLaunchMotion(WanderActor *actor, VecFx32 *velocity);
extern void PlaySoundChecked(int channel, int soundId);

BOOL TryLaunchWanderActor(WanderActor *actor) {
    LaunchMotion *motion;
    int player;
    int heading;
    u32 facing;

    if (actor->state != 0) {
        return FALSE;
    }
    if (func_ov001_02063620() || (data_ov001_020a0480->flags & 0x10) || func_ov001_02064490()) {
        return FALSE;
    }
    heading = actor->heading;
    facing = actor->facing;
    actor->position = *func_ov007_020a100c(actor);
    player = 0;
    if (GrantRewardItem(GetBoundedEntryField(0), &heading, &facing)) {
        actor->heading = heading;
        actor->facing = facing;
        StartLaunchMotion(actor, func_ov001_0206dc60(player));
    } else {
        actor->state = 2;
    }
    motion = &actor->motion[0];
    actor->motion[0].active = TRUE;
    actor->motion[0].airborne = TRUE;
    motion->timer = 0;
    motion->velocity = data_0205344c;
    actor->drawFlags &= ~0x10;
    PlaySoundChecked(0, 0x3a);
    return FALSE;
}
