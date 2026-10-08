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
    int angle;
} LaunchMotion;

typedef struct {
    s16 heading;
    u8 facing;
    u8 weight;
} WanderChoice;

typedef struct {
    int count;
    WanderChoice *choices;
} WanderChoiceSet;

typedef struct {
    u8 pad_00[0x88];
    WanderChoiceSet *choiceSets;
} WanderDef;

typedef struct {
    u8 pad_00[0x8];
    WanderDef *def;
    u8 pad_0c[0x34];
    VecFx32 position;
    u8 pad_4c[0x2];
    u16 drawFlags;
    u8 pad_50[0x8];
    VecFx32 drawPosition;
    LaunchMotion motion[2];
    s16 heading;
    u8 facing;
    s8 state;
    u8 flags;
    s8 phase;
    s8 mode;
    s8 target;
    u16 waitId;
} WanderObject;

typedef struct {
    s16 setIndex;
    s8 mode;
    u8 pad_03;
    union {
        VecFx32 position;
        u8 waitId;
    } arg;
} WanderCommand;

extern const VecFx32 data_0205344c;
extern int func_ov035_020bafc4(void);
extern unsigned int func_0202a9e4(unsigned int range);

void ApplyWanderCommand(WanderObject *object, WanderCommand *command)
{
    int phase = func_ov035_020bafc4();
    WanderChoiceSet *sets;
    WanderChoiceSet *set;
    int total;
    int roll;
    int i;
    VecFx32 zero;

    if (phase == object->phase) {
        return;
    }
    total = 0;
    sets = object->def->choiceSets;
    set = &sets[command->setIndex];
    roll = func_0202a9e4(100);
    object->heading = -1;
    object->facing = 0;
    for (i = 0; i < set->count; i++) {
        total += set->choices[i].weight;
        if (roll < total) {
            object->heading = set->choices[i].heading;
            object->facing = set->choices[i].facing;
            break;
        }
    }
    if (object->heading < 0) {
        object->mode = 4;
        return;
    }
    object->phase = phase;
    object->mode = command->mode;
    object->target = -1;
    switch (command->mode) {
    case 0:
        object->position = command->arg.position;
        object->state = 0;
        object->drawPosition = object->position;
        object->drawFlags |= 0x10;
        break;
    case 3:
        object->position = command->arg.position;
        object->drawPosition = object->position;
        object->waitId = 0;
        object->state = 1;
        object->drawFlags &= ~0x10;
        break;
    case 1:
    case 2:
        object->position = data_0205344c;
        object->state = 1;
        object->waitId = command->arg.waitId;
        object->drawFlags &= ~0x10;
        break;
    }
    object->position.y += 0x800;
    zero = data_0205344c;
    for (i = 0; i < 2; i++) {
        BOOL airborne;
        BOOL first = TRUE;
        if (i != 0) {
            first = FALSE;
        }
        object->motion[i].active = first;
        if (object->state == 1) {
            airborne = FALSE;
        } else {
            airborne = object->motion[i].active;
        }
        object->motion[i].airborne = airborne;
        object->motion[i].timer = 0;
        object->motion[i].origin = object->drawPosition;
        object->motion[i].velocity = zero;
        object->motion[i].scale = 0x1000;
        object->motion[i].angle = 0;
    }
}
