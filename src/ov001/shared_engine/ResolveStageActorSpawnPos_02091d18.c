#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageLink {
    u16 lowBits : 11;
    u16 stageEntry : 3;
    u16 highBits : 2;
    u8 pad_02[0x32];
    VecFx32 position;
} StageLink;

typedef struct StageActor {
    u8 pad_000[0x1D2];
    u16 recordId;
    u8 pad_1D4[0xB8];
    StageLink link;
} StageActor;

typedef struct StageEntry {
    u8 pad_000[0x21C];
    u32 (*getFlags)(struct StageEntry *entry);
} StageEntry;

extern u8 *GetStageEventRecord_0209c0ec(u32 id);
extern u32 func_ov001_0206dc38(void);
extern StageEntry *GetBoundedEntryField_0206db5c(int index);
extern void RandomHorizontalVector_02092634(fx32 length, VecFx32 *out);
extern void VEC_Add_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void SyncStageEntryPosition_02098fbc(u32 id, VecFx32 *outPosition);
extern void func_ov001_02097c78(u8 *record, StageActor *actor, VecFx32 *position);

void ResolveStageActorSpawnPos_02091d18(StageActor *actor, int unused, VecFx32 *position)
{
    u8 *record = GetStageEventRecord_0209c0ec(actor->recordId);
    StageEntry *entry;
    u32 flags;
    VecFx32 offset;

    if ((int)func_ov001_0206dc38() > 0) {
        entry = GetBoundedEntryField_0206db5c((u16)(actor->link.stageEntry - 1));
        if (entry != NULL) {
            if (entry->getFlags != NULL) {
                flags = entry->getFlags(entry);
            } else {
                flags = 0;
            }
            if (flags & 0x40) {
                RandomHorizontalVector_02092634(0x2000, &offset);
                VEC_Add_01ff9e0c(&actor->link.position, &offset, position);
                return;
            }
        }
    }
    SyncStageEntryPosition_02098fbc(actor->link.stageEntry, position);
    func_ov001_02097c78(record, actor, position);
}
