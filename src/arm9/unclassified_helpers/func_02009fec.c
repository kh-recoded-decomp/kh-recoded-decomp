#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    void *callback;
} Registry;

typedef struct {
    u8 pad_00[0x80];
    u32 field_80;
} Context;

extern Registry data_02057620;
extern u8 data_0205764c[];

extern int func_020049f0(void);
extern Context *func_0200913c(void);
extern int func_020023a0(void);
extern void func_02009150(u16 handle);
extern void func_02009c4c(int a, void *dst, u32 value, u32 size);
extern void func_02009198(u16 handle);
extern void func_020023f8(u16 handle);

void func_02009fec(void) {
    data_02057620.callback = (void *)func_02009c4c;
    if (func_020049f0() == 1) {
        Context *ctx = func_0200913c();
        if (ctx->field_80 != 0) {
            u16 handle = (u16)func_020023a0();
            func_02009150(handle);
            ctx = func_0200913c();
            func_02009c4c(0, data_0205764c, ctx->field_80, 0x88);
            func_02009198(handle);
            func_020023f8(handle);
        }
    }
}
