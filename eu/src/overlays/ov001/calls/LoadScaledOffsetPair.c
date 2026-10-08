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

extern const FilePath sOv001_EnPaUPBin_0209e61c;
extern OffsetTable *Archive_LoadFile(const char *path, u32 flags);
extern void NNSi_FndFreeFromDefaultHeap(void *ptr);
extern fx32 FX_Mul(fx32 a, fx32 b);

void LoadScaledOffsetPair(fx32 *out, int index)
{
    FilePath path = sOv001_EnPaUPBin_0209e61c;
    OffsetPair pair;
    OffsetTable *table;
    OffsetPair *pairs;

    if (index == 0) {
        out[0] = 0;
        out[1] = 0;
        return;
    }
    table = Archive_LoadFile(path.name, 11);
    pairs = (OffsetPair *)((u16 *)table + 1);
    pair = pairs[index];
    NNSi_FndFreeFromDefaultHeap(table);
    out[0] = FX_Mul(pair.x << 4, 0x1e000);
    out[1] = FX_Mul(pair.y << 4, 0x1e000);
}
