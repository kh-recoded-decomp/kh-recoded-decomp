#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MotionBody {
    u8 pad_00[0xa8];
    VecFx32 position;
} MotionBody;

typedef struct MotionLink {
    MotionBody *body;
    u32 unk04;
    VecFx32 velocity;
} MotionLink;

typedef struct PartyActor {
    u8 pad_000[0x84c];
    VecFx32 move;
    void *pendingPath;
    u8 pad_85c[0xd18 - 0x85c];
    MotionLink *link;
    u8 pad_d1c[0xef4 - 0xd1c];
    u32 flags;
} PartyActor;

extern const VecFx32 data_02053438;
extern void func_ov001_02089394(PartyActor *actor);
extern void func_ov001_02089bd4(PartyActor *actor);
extern void func_ov001_02089208(PartyActor *actor, VecFx32 *out);
extern void func_ov001_02089aa8(PartyActor *actor);
extern void Actor_StepPeriodicAnimEvent_020899ac(PartyActor *actor);
extern void AlignPartyLeaderToActor_020891b4(PartyActor *actor);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_Mag_01ff9f28(const VecFx32 *v);
extern void func_02038e6c(MotionLink *link, int mode);
extern void Obj_SetPosition_0203569c(MotionBody *body, const VecFx32 *position);

static inline void SetGroundVelocity(MotionLink *link, const VecFx32 *velocity)
{
    link->velocity.x = velocity->x;
    link->velocity.y = 0;
    link->velocity.z = velocity->z;
}

void UpdatePartyActorMotion_0208a114(PartyActor *actor)
{
    VecFx32 drift;
    VecFx32 position;
    u32 flags;

    drift.z = 0;
    drift.y = 0;
    drift.x = 0;
    flags = actor->flags;
    if (flags & 0x200) {
        func_ov001_02089394(actor);
        flags = actor->flags;
        if (flags == 0) {
            return;
        }
    }
    if ((flags & 0x20) || (flags & 0x4000)) {
        return;
    }
    func_ov001_02089bd4(actor);
    if (actor->flags & 0x40) {
        func_ov001_02089208(actor, &drift);
        VEC_Add_01ff9e0c(&drift, &actor->move, &drift);
        if (VEC_Mag_01ff9f28(&drift) <= 0x10) {
            drift.z = 0;
            drift.y = 0;
            drift.x = 0;
        }
        SetGroundVelocity(actor->link, &drift);
    }
    if (actor->pendingPath != NULL) {
        func_ov001_02089aa8(actor);
    }
    if (actor->flags & 0x10) {
        if (VEC_Mag_01ff9f28(&actor->move) != 0 || VEC_Mag_01ff9f28(&drift) != 0) {
            func_02038e6c(actor->link, 0);
        }
    } else if (VEC_Mag_01ff9f28(&actor->move) != 0 || VEC_Mag_01ff9f28(&drift) != 0) {
        position = actor->link->body->position;
        if (VEC_Mag_01ff9f28(&drift) != 0) {
            VEC_Add_01ff9e0c(&position, &drift, &position);
        } else {
            VEC_Add_01ff9e0c(&position, &actor->move, &position);
        }
        Obj_SetPosition_0203569c(actor->link->body, &position);
    }
    if (actor->flags & 0x80) {
        Actor_StepPeriodicAnimEvent_020899ac(actor);
    }
    if (actor->flags & 0x800) {
        AlignPartyLeaderToActor_020891b4(actor);
    }
    SetGroundVelocity(actor->link, &data_02053438);
}
