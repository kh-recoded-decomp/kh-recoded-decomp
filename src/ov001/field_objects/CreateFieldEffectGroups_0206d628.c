#include "nitro/types.h"

typedef struct {
    u32 resourceId;
    u32 animationId;
    s32 slotCount;
    u32 modelId;
    BOOL fixedSlots;
} EntryGroupDesc;

typedef struct {
    u32 fileIndex;
    BOOL fixedSlots;
    s32 slotCount;
} EffectGroupDef;

typedef struct {
    EffectGroupDef defs[2];
} EffectGroupTable;

typedef struct {
    u8 pad_00[0xb4];
    u16 groupIds[2];
} FieldEffects;

extern FieldEffects *data_ov001_020a049c;
extern EffectGroupTable data_ov001_0209daec;

extern void ZeroBytes0x14_020a8adc(void *obj);
extern u32 func_ov001_0206dba0(int kind);
extern u16 func_ov021_020a89a8(EntryGroupDesc *desc);

void CreateFieldEffectGroups_0206d628(void) {
    FieldEffects *effects = data_ov001_020a049c;
    EntryGroupDesc desc;
    EffectGroupTable table;
    int i;

    ZeroBytes0x14_020a8adc(&desc);
    table = data_ov001_0209daec;
    desc.animationId = 1;
    for (i = 0; i < 2; i++) {
        EffectGroupDef *def = &table.defs[i];
        u32 fileIndex = def->fileIndex;
        desc.modelId = (((func_ov001_0206dba0(2) + 0x8000) & 0xfffffc) << 7) | (1u << 31) | (fileIndex & 0x1ff);
        desc.animationId = (((func_ov001_0206dba0(2) + 0x8000) & 0xfffffc) << 7) | 0x80000000 | ((fileIndex + 1) & 0x1ff);
        desc.slotCount = def->slotCount;
        desc.fixedSlots = def->fixedSlots;
        effects->groupIds[i] = func_ov021_020a89a8(&desc);
    }
}
