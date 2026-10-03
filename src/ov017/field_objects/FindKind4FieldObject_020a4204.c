#include "nitro/types.h"

typedef struct FieldDef {
    u8 pad_00[0x5a];
    u8 kind;
} FieldDef;

extern int func_ov001_02087248(void);
extern FieldDef *func_ov001_02087214(int index);

FieldDef *FindKind4FieldObject_020a4204(void)
{
    int i;
    int count;
    FieldDef *def;

    count = func_ov001_02087248();
    for (i = 0; i < count; i++) {
        def = func_ov001_02087214(i);
        if (def->kind == 4) {
            return def;
        }
    }
    return NULL;
}
