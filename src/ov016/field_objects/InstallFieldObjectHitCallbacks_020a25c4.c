#include "nitro/types.h"

typedef void (*HitCallback)(void);

typedef struct {
    u8 pad_000[0x17c];
    HitCallback touchCallback;
    void *touchContext;
    u8 pad_184[0x18c - 0x184];
    HitCallback hitCallback;
    void *hitContext;
} FieldActor;

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x77 - 0x33];
    u8 mode;
    u8 pad_78[0xbd - 0x78];
    u8 unk_BD_low : 4;
    u8 phase : 4;
} FieldObject;

extern FieldActor *func_02036240(u32 actorId);
extern void func_ov016_020a56bc(void);
extern void func_ov016_020a4694(void);
extern void OnMode11FieldObjectHit_020a3b44(void);
extern void func_ov016_020a566c(void);
extern void func_ov016_020a565c(void);

void InstallFieldObjectHitCallbacks_020a25c4(FieldObject *obj)
{
    FieldActor *actor = func_02036240(obj->actorId);
    HitCallback callback;

    actor->hitCallback = NULL;
    actor->hitContext = NULL;
    actor->touchCallback = NULL;
    actor->touchContext = NULL;
    if (obj->phase == 3 || obj->phase == 4 || obj->mode == 3 || obj->mode == 7 || obj->mode == 11 ||
        obj->mode == 5) {
        switch (obj->mode) {
        case 3:
            callback = func_ov016_020a56bc;
            break;
        case 7:
            callback = func_ov016_020a4694;
            break;
        case 11:
            callback = OnMode11FieldObjectHit_020a3b44;
            break;
        default:
            callback = func_ov016_020a566c;
            break;
        }
        actor->hitCallback = callback;
        actor->hitContext = obj;
    }
    if (obj->mode == 5) {
        actor->touchCallback = func_ov016_020a565c;
        actor->touchContext = obj;
    }
}
