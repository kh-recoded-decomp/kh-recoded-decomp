#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xbd];
    u8 unk_BD_low : 4;
    u8 phase : 4;
    u8 pad_be[2];
    u32 flags;
} FieldObject;

extern void func_ov016_020a4d10(FieldObject *obj);
extern void func_ov016_020a2ca4(FieldObject *obj);
extern void func_ov032_020bf830(FieldObject *obj);
extern void func_ov016_020a4a94(FieldObject *obj);

void DispatchFieldObjectPhase_020a582c(FieldObject *obj)
{
    if (obj->flags & 8) {
        return;
    }
    switch (obj->phase) {
    case 2:
    case 4:
        if (!(obj->flags & 0x500)) {
            func_ov016_020a2ca4(obj);
        }
        break;
    case 1:
        func_ov016_020a4d10(obj);
        break;
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
        func_ov032_020bf830(obj);
        break;
    }
    if (obj->flags & 0x100) {
        func_ov016_020a4a94(obj);
    }
}
