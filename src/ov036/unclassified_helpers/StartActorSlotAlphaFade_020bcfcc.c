#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorSlot {
    u8 pad_00[0x2a];
    u8 alpha : 5;
    u8 unk_2A_5 : 3;
    u8 pad_2B[0x39];
    fx32 startAlpha;
    fx32 endAlpha;
    s32 duration;
    s32 timer;
    u8 pad_74[0x14];
    u16 flags;
    u8 pad_8A[0x12];
} ActorSlot;

typedef struct ActorSlotWork {
    u8 pad_0000[0x1090];
    ActorSlot *slots;
} ActorSlotWork;

typedef struct ActorSlotContext {
    u32 unk_00;
    ActorSlotWork *work;
} ActorSlotContext;

extern ActorSlotContext data_ov036_020c3920;
extern int func_ov036_020bb7c0(int actorId);

void StartActorSlotAlphaFade_020bcfcc(int actorId, int startAlpha, int endAlpha, s32 duration)
{
    ActorSlotWork *work = data_ov036_020c3920.work;
    ActorSlot *slot = &work->slots[func_ov036_020bb7c0(actorId)];

    slot->duration = duration;
    slot->timer = duration;
    if (startAlpha == -1) {
        slot->startAlpha = slot->alpha << 12;
    } else {
        slot->startAlpha = startAlpha << 12;
    }
    if (endAlpha == -1) {
        slot->endAlpha = slot->alpha << 12;
    } else {
        slot->endAlpha = endAlpha << 12;
    }
    slot->alpha = (u8)(slot->startAlpha >> 12);
    slot->flags |= 4;
}
