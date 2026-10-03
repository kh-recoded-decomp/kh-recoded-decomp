#include "nitro/fx_types.h"

typedef struct {
    u32 baseIndex : 9;
    u8 pad_04[4];
    u32 bits : 3;
    u32 scattering : 1;
    u16 memberCount;
    u8 pad_0e[0x126];
    VecFx32 anchor;
} GroupEntry;

typedef struct {
    u8 pad_00[4];
    u32 unitTable;
} GroupOwner;

extern const VecFx32 data_02053438;
extern GroupEntry *func_ov032_020bbc60(void *group);
extern u16 *func_ov032_020bbc78(void *unit);
extern u32 func_ov001_0208635c(u32 table, u32 index);
extern BOOL IsFieldUnitPhase6_020a6a64(void *unit);

void ResetGroupMemberFlags_020be654(GroupOwner *group)
{
    GroupEntry *entry = func_ov032_020bbc60(group);
    int i;

    for (i = 0; i < (u8)entry->memberCount; i++) {
        void *unit = (void *)func_ov001_0208635c(group->unitTable, entry->baseIndex + i);
        if (IsFieldUnitPhase6_020a6a64(unit) == FALSE) {
            *func_ov032_020bbc78(unit) = 0;
        }
    }
    entry->anchor = data_02053438;
    entry->scattering = 0;
}
