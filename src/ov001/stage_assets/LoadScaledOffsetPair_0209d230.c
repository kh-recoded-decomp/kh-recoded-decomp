#include "nitro/types.h"
#include "nitro/fx_types.h"

#pragma opt_propagation off

typedef struct {
    char name[13];
} FilePath;

typedef struct {
    s16 x;
    s16 y;
} OffsetPair;

typedef struct {
    u16 count;
    OffsetPair pairs[1];
} OffsetTable;

extern const FilePath data_ov001_0209e5f4;
extern OffsetTable *func_0202c478(const char *path, u32 flags);
extern void NNSi_FndFreeFromDefaultHeap_0202a1c4(void *ptr);
extern fx32 func_02006450(fx32 a, fx32 b);

void LoadScaledOffsetPair_0209d230(fx32 *out, int index)
{
    FilePath path = data_ov001_0209e5f4;
    OffsetPair pair;
    OffsetTable *table;
    OffsetPair *pairs;

    if (index == 0) {
        out[0] = 0;
        out[1] = 0;
        return;
    }
    table = func_0202c478(path.name, 11);
    pairs = (OffsetPair *)((u16 *)table + 1);
    pair = pairs[index];
    NNSi_FndFreeFromDefaultHeap_0202a1c4(table);
    out[0] = func_02006450(pair.x << 4, 0x1e000);
    out[1] = func_02006450(pair.y << 4, 0x1e000);
}
