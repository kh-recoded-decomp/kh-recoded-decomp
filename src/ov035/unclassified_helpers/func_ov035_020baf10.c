#include "nitro/types.h"

extern u32 data_ov035_020bc4e0;
extern u16 func_ov001_02064574(u32 id, int size);
extern void func_ov001_0206459c(u32 id, int size, int value);
extern int func_ov001_020645c8(u32 id);
extern void func_ov001_020645dc(u32 id);
extern u32 func_ov001_0207f038(u8 a, u8 b);
extern void func_ov001_0207f6f4(u32 a, u32 b);
extern int random_next_scaled_0202aa04(u32 scale);

void func_ov035_020baf10(u32 scale, s16 *table, u8 a, u8 b) {
    int index;
    u16 picked;
    u32 encoded;
    u32 extra;

    if (func_ov001_020645c8(0x379b) == 0) {
        index = random_next_scaled_0202aa04(scale);
        func_ov001_0206459c(0x3791, 10, (int)table[index]);
        func_ov001_020645dc(0x379b);
    }
    *(u8 *)(data_ov035_020bc4e0 + 0x1f) = a;
    *(u8 *)(data_ov035_020bc4e0 + 0x20) = b;
    picked = func_ov001_02064574(0x3791, 10);
    *(u16 *)(data_ov035_020bc4e0 + 0x30) = picked;
    encoded = func_ov001_0207f038(*(u8 *)(data_ov035_020bc4e0 + 0x1f),
                                  *(u8 *)(data_ov035_020bc4e0 + 0x20));
    extra = func_ov001_020645c8(0x3702);
    func_ov001_0207f6f4(encoded, extra);
}
