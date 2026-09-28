#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u32 unk_0c;
    u32 unk_10;
} DataBlock_02056fe0;

extern DataBlock_02056fe0 data_02056fe0;

void func_02009144(u32 param1, u32 param2)
{
    data_02056fe0.unk_0c = param1;
    data_02056fe0.unk_10 = param2;
}
