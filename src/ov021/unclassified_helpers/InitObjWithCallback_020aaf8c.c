#include "nitro/types.h"

extern void func_01ff8740(u32 value, void *dest, u32 size);
extern void func_ov021_020aaf3c(void);

typedef void (*Callback)(void);

typedef struct {
    u32 field0;
    u32 field1;
    u8 pad_008[0x2c];
    Callback callback;
} InitObj;

void InitObjWithCallback_020aaf8c(InitObj *obj, u32 arg1, u32 arg2)
{
    func_01ff8740(0, obj, 0x3c);
    obj->field0 = arg1;
    obj->field1 = arg2;
    obj->callback = func_ov021_020aaf3c;
}
