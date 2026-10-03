#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x18];
    s16 rareScale;
    u8 pad_1a[0x1c6];
} RowEntry;

typedef struct {
    u8 pad_00[0xcc];
    RowEntry *rows;
} RowOwner;

extern const u8 data_ov032_020bff6c[];
extern u8 *func_ov032_020bbbd4(void *owner, s32 index);
extern void func_01ff8ad8(const void *src, void *dst, u32 size);
extern int PickWeightedIndex_020bbe84(u8 *weights, int count);

u8 RollRowDropItem_020bbecc(RowOwner *owner, int index)
{
    RowEntry *row = &owner->rows[index];
    u8 weights[8];
    int scaled;
    int scale;

    func_01ff8ad8(func_ov032_020bbbd4(owner, index) + 0x1f, weights, 8);
    scale = row->rareScale;
    scaled = weights[7] * scale / 4096;
    if (scaled == 0 && scale != 0) {
        scaled = 1;
    }
    weights[7] = scaled;
    return data_ov032_020bff6c[PickWeightedIndex_020bbe84(weights, 8)];
}
