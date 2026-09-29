#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct MarkList MarkList;

typedef struct MarkSource {
    u8 pad_000[0xd4];
    VecFx32 position;
    u8 pad_0E0[0x150 - 0xe0];
    s32 *surfaceType;
} MarkSource;

extern s32 func_ov059_020cd950(s32 *surfaceType);
extern void func_ov059_020cdd68(MarkList *list, s32 markKind, VecFx32 *position);

void MarkList_AddAtObject_020cde4c(MarkList *list, MarkSource *source)
{
    s32 markKind = func_ov059_020cd950(source->surfaceType);

    func_ov059_020cdd68(list, markKind, &source->position);
}
