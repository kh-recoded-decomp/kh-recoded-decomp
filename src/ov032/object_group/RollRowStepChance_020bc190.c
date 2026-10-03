#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 low : 16;
    u32 step : 6;
    u8 pad_0c[0x1d4];
} RowEntry;

typedef struct {
    u8 pad_00[0xcc];
    RowEntry *rows;
} RowOwner;

typedef struct {
    u8 pad_00[0x10];
    u8 sequence[11];
} RowDefinition;

typedef struct {
    u8 failWeight;
    u8 passWeight;
} ChancePair;

extern const ChancePair data_ov032_020bff74[];
extern RowDefinition *func_ov032_020bbbd4(void *owner, s32 index);
extern unsigned int random_next_scaled_0202aa04(unsigned int upperBound);

BOOL RollRowStepChance_020bc190(RowOwner *owner, int index)
{
    RowDefinition *definition = func_ov032_020bbbd4(owner, index);
    const ChancePair *chance = &data_ov032_020bff74[definition->sequence[(u8)owner->rows[index].step]];

    if (chance->failWeight == 0) {
        return TRUE;
    }
    if (chance->passWeight == 0) {
        return FALSE;
    }
    if (chance->passWeight >= (int)random_next_scaled_0202aa04(chance->passWeight + chance->failWeight)) {
        return TRUE;
    }
    return FALSE;
}
