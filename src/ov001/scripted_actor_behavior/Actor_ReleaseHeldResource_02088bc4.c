#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorModel {
    u8 pad_000[0x370];
    u8 heldResource[4];
} ActorModel;

typedef struct Actor {
    u8 pad_000[0x894];
    ActorModel model;
    u8 pad_c08[0xef4 - 0xc08];
    u32 flags;
    u8 pad_ef8[8];
    s32 partyIndex;
} Actor;

typedef struct PartyEntry {
    u8 pad_000[0x6ac];
    VecFx32 heldOffset;
} PartyEntry;

extern const VecFx32 data_02053438;

extern s32 func_ov001_02063a38(void);
extern void ReleaseResourceAndDetach_0202eee8(u8 *object);
extern PartyEntry *GetBoundedEntryField_0206db5c(int index);

void Actor_ReleaseHeldResource_02088bc4(Actor *actor)
{
    ActorModel *model = &actor->model;

    if (func_ov001_02063a38() == 7) {
        return;
    }
    ReleaseResourceAndDetach_0202eee8(model->heldResource);
    if (actor->partyIndex < 3) {
        GetBoundedEntryField_0206db5c(actor->partyIndex)->heldOffset = data_02053438;
    }
    actor->flags &= ~0x800;
}
