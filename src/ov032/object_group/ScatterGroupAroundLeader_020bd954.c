#include "nitro/fx_types.h"

typedef struct {
    u32 baseIndex : 9;
    u8 pad_04[4];
    u32 bits : 3;
    u32 scattering : 1;
    u16 memberCount;
    u8 pad_0e[0x1ca];
    int leaderTimer;
} GroupEntry;

typedef struct {
    u16 flags;
    u8 pad_02[0x16];
    VecFx32 offset;
} MemberState;

typedef struct {
    u8 pad_00[4];
    u32 unitTable;
} GroupOwner;

extern GroupEntry *func_ov032_020bbc60(void *group);
extern MemberState *func_ov032_020bbc78(void *unit);
extern u32 func_ov001_0208635c(u32 table, u32 index);
extern BOOL IsFieldUnitPhase6_020a6a64(void *unit);
extern void PickJitteredLeaderOffset_020bd8bc(void *unit, VecFx32 *out);

void ScatterGroupAroundLeader_020bd954(GroupOwner *group)
{
    GroupEntry *entry = func_ov032_020bbc60(group);
    int i;

    for (i = 0; i < (u8)entry->memberCount; i++) {
        void *unit = (void *)func_ov001_0208635c(group->unitTable, entry->baseIndex + i);
        MemberState *state = func_ov032_020bbc78(unit);
        if (IsFieldUnitPhase6_020a6a64(unit) == FALSE) {
            state->flags = 0;
        }
        PickJitteredLeaderOffset_020bd8bc(unit, &state->offset);
    }
    entry->leaderTimer = 0;
    entry->scattering = 0;
}
