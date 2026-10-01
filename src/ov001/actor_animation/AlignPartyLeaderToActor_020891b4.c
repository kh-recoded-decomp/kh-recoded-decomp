#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PartyEntry {
    u8 pad_000[0x6ac];
    VecFx32 offset;
} PartyEntry;

typedef struct FieldActor {
    u8 pad_000[0x894];
    u8 anchor[0x66c];
    int partyIndex;
} FieldActor;

extern void func_ov001_02089118(VecFx32 *out, void *anchor);
extern int func_ov001_02063a38(void);
extern PartyEntry *GetBoundedEntryField_0206db5c(int index);
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_ov001_02089180(FieldActor *actor);

void AlignPartyLeaderToActor_020891b4(FieldActor *actor)
{
    VecFx32 position;
    VecFx32 anchor;
    PartyEntry *entry;

    func_ov001_02089118(&anchor, actor->anchor);
    position = anchor;
    if (func_ov001_02063a38() == 7) {
        return;
    }
    if (actor->partyIndex < 3) {
        entry = GetBoundedEntryField_0206db5c(actor->partyIndex);
        VEC_Subtract_01ff9e3c(&entry->offset, &position, &entry->offset);
    }
    func_ov001_02089180(actor);
}
