#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x14];
    u8 anim[1];
} EffectObject;

typedef struct {
    u8 kind;
    u8 pad_001[7];
    u32 flags;
    u8 pad_00c[0x114];
    int frame;
    u8 pad_124[0x4c];
    u8 anim[2];
    s16 slot;
    u8 pad_174[0x1c0];
    EffectObject *child;
} StageActor;

typedef struct {
    u8 pad_000[0x10c];
    u8 anim[0x240];
    EffectObject *effects[2];
} StageWork;

extern u8 *data_ov035_020bc4e0;
extern void func_01ffb2f8(void *anim, u16 index, int frame);
extern void SetAnimationFrameIfChanged(StageActor *actor, int frame);

void SetStageActorFrame(StageActor *actor, int frame) {
    StageWork *work = *(StageWork **)(data_ov035_020bc4e0 + 0xb8);
    int slot = actor->slot;
    EffectObject *effect;
    int index;
    int i;

    for (i = 0; i < 5; i++) {
        func_01ffb2f8(actor->anim, i, frame);
        if (actor->kind == 0xff) {
            func_01ffb2f8(work->anim, i, frame);
        }
    }
    SetAnimationFrameIfChanged(actor, frame);
    switch (actor->kind) {
    case 0xff:
        index = slot - 5;
        if (index >= 0 && index < 4) {
            effect = work->effects[0];
            func_01ffb2f8(effect->anim, 0, frame);
            func_01ffb2f8(effect->anim, 1, frame);
            func_01ffb2f8(effect->anim, 2, frame);
        }
        break;
    case 0xfd:
        if (slot < 9) {
            index = slot - 5;
        } else {
            index = slot - 6;
        }
        if (index >= 0 && index < 8) {
            effect = work->effects[1];
            func_01ffb2f8(effect->anim, 0, frame);
            func_01ffb2f8(effect->anim, 1, frame);
            func_01ffb2f8(effect->anim, 2, frame);
        }
        break;
    case 0x16:
        func_01ffb2f8(actor->child->anim, 0, frame);
        break;
    }
    actor->flags |= 2;
    actor->frame = frame;
}
