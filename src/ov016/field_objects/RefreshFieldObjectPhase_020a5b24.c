#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x70];
    u16 drawFlags;
    u8 pad_72[0x90 - 0x72];
    s16 linkA;
    s16 linkB;
    u8 pad_94[0xbd - 0x94];
    u8 unk_BD_low : 4;
    u8 phase : 4;
} FieldObject;

extern void func_ov016_020a6064(FieldObject *obj);
extern void LoadMessageFiles_020bf3f0(FieldObject *obj);
extern void func_ov016_020a232c(FieldObject *obj);
extern void func_ov016_020a4a64(FieldObject *obj);

void RefreshFieldObjectPhase_020a5b24(FieldObject *obj)
{
    s16 link;
    int phase;

    func_ov016_020a6064(obj);
    if (obj->phase >= 5) {
        LoadMessageFiles_020bf3f0(obj);
    } else {
        func_ov016_020a232c(obj);
    }
    phase = obj->phase;
    if (phase == 1 && ((link = obj->linkA) != -1 || obj->linkB != -1)) {
        if (link != -1) {
            obj->drawFlags |= 8;
        }
    } else if ((u8)(phase + 0xfd) <= 1) {
        func_ov016_020a4a64(obj);
    }
}
