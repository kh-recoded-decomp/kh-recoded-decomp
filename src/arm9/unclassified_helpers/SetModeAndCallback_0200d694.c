#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    u32 field_2c;
    u8 pad_30[0x1c];
    u32 field_4c;
} Obj;

extern void func_0200d5d8(Obj *obj);
extern void func_0200ded0(Obj *obj);

extern int data_02057b84;
extern void (*data_02055c40)(Obj *obj);

int SetModeAndCallback_0200d694(int mode)
{
    int previous = data_02057b84;
    data_02057b84 = mode;
    if (mode != 0) {
        data_02055c40 = func_0200d5d8;
    } else {
        data_02055c40 = func_0200ded0;
    }
    return previous;
}
