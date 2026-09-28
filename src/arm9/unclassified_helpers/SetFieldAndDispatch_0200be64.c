#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 field_08;
    u8 pad_0c[0x24];
    u32 field_30;
    u16 field_34;
    u16 field_36;
    u32 field_38;
} SomeObject;

extern void func_0200c6fc(SomeObject *object, int a, int b, int c);

void SetFieldAndDispatch_0200be64(SomeObject *object, s16 value) {
    object->field_34 = value;
    object->field_30 = object->field_08;
    object->field_36 = 0;
    object->field_38 = 0;
    func_0200c6fc(object, 2, 1, 0);
}
