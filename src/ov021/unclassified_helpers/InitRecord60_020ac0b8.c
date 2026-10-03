#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Record60 {
    u8 pad_00[0x1c];
    int index;
    u8 pad_20[0x34];
    fx32 scale;
    u8 pad_58[8];
} Record60;

extern void func_01ff8830(void *dst, int value, int size);

void InitRecord60_020ac0b8(Record60 *record)
{
    func_01ff8830(record, 0, sizeof(Record60));
    record->scale = 0x1000;
    record->index = -1;
}
