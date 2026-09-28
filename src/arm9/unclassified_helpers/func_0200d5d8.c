#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    u32 field_2c;
    u8 pad_30[0x1c];
    u32 field_4c;
} Obj;

extern void func_0200ded0(Obj *obj);

void func_0200d5d8(Obj *obj)
{
    u32 saved2c = obj->field_2c;
    u32 saved4c = obj->field_4c;
    obj->field_2c = 0;
    obj->field_4c = 0;
    func_0200ded0(obj);
    obj->field_2c = saved2c;
    obj->field_4c = saved4c;
}
