#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 flags;
} StatusBlock_02056fe0;

typedef struct {
    u8 pad_00[0x1c];
    u32 unk_1c;
} DataBlock_020574e0;

extern StatusBlock_02056fe0 data_02056fe0;
extern DataBlock_020574e0 data_020574e0;
extern void func_02002b60(u32 value);

void func_020094e4(int param1, u32 param2, int param3)
{
    if ((param1 == 0xb) && (param3 != 0)) {
        data_02056fe0.flags = data_02056fe0.flags & 0xffffffdf;
        func_02002b60(data_020574e0.unk_1c);
    }
}
