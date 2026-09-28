#include "nitro/types.h"

extern int func_0200b08c(void *obj);
extern BOOL func_0200d290(void *obj);
extern void func_0200b11c(void *obj);

typedef struct {
    u8 pad_00[4];
    u32 field_04;
    u8 pad_08[4];
    u32 field_0c;
    u8 pad_10[4];
    u32 field_14;
    u32 field_18;
    u32 field_1c;
} Inner;

typedef struct {
    u8 pad_00[0x14];
    u32 flags;
    u8 pad_18[8];
    Inner *inner;
} Outer;

u32 ResetInnerFieldsIfFlagSet_0200d1fc(Outer *obj)
{
    u32 result = 0;
    u32 flagSet = (obj->flags & 2) ? 1 : 0;
    if (flagSet != 0) {
        Inner *inner = obj->inner;
        int wasSet = func_0200b08c(obj);
        if (func_0200d290(obj)) {
            obj->flags &= ~4;
            result = inner->field_1c;
            inner->field_04 = inner->field_14;
            inner->field_0c = inner->field_18;
            inner->field_1c = 0;
        }
        if (wasSet) {
            func_0200b11c(obj);
        }
    }
    return result;
}
