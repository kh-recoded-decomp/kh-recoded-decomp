#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xc];
    u8 effectId;
} HitParams;

typedef struct {
    u8 pad_00[0x76];
    s8 weight;
    u8 mode;
    u8 pad_78[0xbd - 0x78];
    u8 unk_BD_low : 4;
    u8 phase : 4;
    u8 unk_BE_low : 4;
    u8 state : 4;
    s8 currentWeight;
    u8 pad_c0[0xc8 - 0xc0];
    int soundId;
} FieldObject;

extern BOOL func_ov001_0208764c(FieldObject *obj, HitParams *params);
extern BOOL func_ov016_020a3258(FieldObject *obj, HitParams *params);
extern void InitializeFieldEffect_020a3be4(FieldObject *obj, u8 effectId);
extern void func_ov032_020bfba4(FieldObject *obj, int arg);
extern void func_ov016_020a6d40(FieldObject *obj, BOOL hasEffect);

int HandleFieldObjectHit_020a5084(FieldObject *obj, HitParams *params)
{
    int result;

    if (func_ov001_0208764c(obj, params)) {
        return 0x10;
    }
    if (obj->state == 0) {
        result = 1;
        if (obj->weight > 1) {
            obj->soundId = 0x222;
        }
        if (func_ov016_020a3258(obj, params)) {
            result = 0;
        } else if (obj->mode == 11) {
            InitializeFieldEffect_020a3be4(obj, params->effectId);
            return 0;
        }
        if (obj->weight == 0) {
            return result;
        }
        if (obj->phase >= 5) {
            func_ov032_020bfba4(obj, 0);
        } else {
            obj->currentWeight--;
        }
        if (obj->currentWeight > 0) {
            return 0;
        }
        func_ov016_020a6d40(obj, params->effectId != 0xff);
    }
    return 0;
}
