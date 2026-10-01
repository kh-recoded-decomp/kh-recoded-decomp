#include "nitro/types.h"

typedef struct AnimObject {
    u32 unk_00;
    u16 frameData[1];
} AnimObject;

typedef struct ActorBody {
    AnimObject *anim;
} ActorBody;

typedef struct Actor {
    u32 unk_000;
    int eventPeriod;
    int eventId;
    u8 pad_00c[0xd18 - 0xc];
    ActorBody *body;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 flags;
} Actor;

extern void func_ov001_02089374(Actor *actor);
extern int Anim_GetFrame_0202f4a0(u16 *frameData, int arg);
extern s64 SignedDivMod_02023dbc(int numerator, int denominator);
extern void func_ov001_02089948(Actor *actor, int eventId);

void Actor_StepPeriodicAnimEvent_020899ac(Actor *actor)
{
    int frame;

    if (actor->flags & 0x100) {
        func_ov001_02089374(actor);
        return;
    }
    frame = Anim_GetFrame_0202f4a0(actor->body->anim->frameData, 0) >> 12;
    if ((int)(SignedDivMod_02023dbc(frame, actor->eventPeriod) >> 32) == 0 && frame != 0) {
        func_ov001_02089948(actor, actor->eventId);
    }
}
