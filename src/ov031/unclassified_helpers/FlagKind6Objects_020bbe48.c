#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x5a];
    u8 kind;
} ObjectInfo;

typedef struct FieldObject FieldObject;

struct FieldObject {
    FieldObject *next;
    ObjectInfo *info;
};

extern FieldObject *func_ov001_0208723c(void);
extern void SetFlagBit8_020a37b0(FieldObject *object);

void FlagKind6Objects_020bbe48(void)
{
    FieldObject *object;

    for (object = func_ov001_0208723c(); object != NULL; object = object->next) {
        if (object->info->kind == 6) {
            SetFlagBit8_020a37b0(object);
        }
    }
}
