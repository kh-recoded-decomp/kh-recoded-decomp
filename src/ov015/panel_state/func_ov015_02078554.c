#include "nitro/types.h"

typedef struct {
    s16 kind;
    s16 id;
    s16 count;
} PanelDescriptor;

extern void func_0202e060(int dst, u32 value, int count);
extern void func_02051d3c(int a, int b);
extern void func_02051dfc(int a);
extern int func_02051ec8(int id);
extern int func_ov002_02066374(int param);
extern void func_ov002_020663d0(int param1, u32 value, int mode);
extern void func_ov002_02069d04(int id, int param);
extern u32 func_ov027_020ba2a8(void *ptr, int mode);
extern u8 *data_ov015_020812e0;

int func_ov015_02078554(int param1, PanelDescriptor *desc) {
    int offset;
    u32 value;
    int base;

    if (desc->kind == 0) {
        func_02051d3c(0, 1);
        base = func_02051ec8(desc->id);
        func_ov002_020663d0(param1, *(u32 *)(base + 0x40), 0x3f);
        func_02051dfc(0);
        if (desc->count > 0) {
            offset = func_ov002_02066374(param1);
            value = func_ov027_020ba2a8(data_ov015_020812e0 + 0x65e0, 0x37);
            func_0202e060(param1 + offset * 2, value, desc->count);
        }
    } else {
        func_ov002_02069d04(desc->id, param1);
    }
    return param1;
}
