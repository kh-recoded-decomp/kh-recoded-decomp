#include "nitro/types.h"

extern u32 gMovieContextState;
extern u16 ReadSessionPackedBits(u32 id, int size);
extern void WriteSessionPackedBits(u32 id, int size, int value);
extern int IsSessionFlagSet(u32 id);
extern void SetSessionFlag(u32 id);
extern u32 func_ov001_0207f060(u8 a, u8 b);
extern void FieldObject_SetEnabled(u32 a, u32 b);
extern int random_next_scaled(u32 scale);

void func_ov035_020baf30(u32 scale, s16 *table, u8 a, u8 b) {
    int index;
    u16 picked;
    u32 encoded;
    u32 extra;

    if (IsSessionFlagSet(0x379b) == 0) {
        index = random_next_scaled(scale);
        WriteSessionPackedBits(0x3791, 10, (int)table[index]);
        SetSessionFlag(0x379b);
    }
    *(u8 *)(gMovieContextState + 0x1f) = a;
    *(u8 *)(gMovieContextState + 0x20) = b;
    picked = ReadSessionPackedBits(0x3791, 10);
    *(u16 *)(gMovieContextState + 0x30) = picked;
    encoded = func_ov001_0207f060(*(u8 *)(gMovieContextState + 0x1f),
                                  *(u8 *)(gMovieContextState + 0x20));
    extra = IsSessionFlagSet(0x3702);
    FieldObject_SetEnabled(encoded, extra);
}
