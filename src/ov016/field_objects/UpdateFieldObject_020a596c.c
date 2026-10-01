#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0xa8];
    VecFx32 position;
    u8 pad_0b4[0x119 - 0xb4];
    u8 boxInitialized;
    u8 pad_11a[0x130 - 0x11a];
    u8 point[4];
    u8 bounds[0x18];
    u8 pad_14c[4];
    u8 delta[0xc];
    u8 movedBounds[0x18];
} FieldActor;

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0x77 - 0x44];
    u8 mode;
    u8 pad_78[0x84 - 0x78];
    VecFx32 lastPosition;
    u8 pad_90[0xbe - 0x90];
    u8 unk_BE_low : 4;
    u8 state : 4;
    u8 pad_bf;
    u32 flags;
    u8 pad_c4[4];
    s32 timer;
} FieldObject;

extern FieldActor *func_02036240(u32 actorId);
extern void func_0203afa0(void *point, VecFx32 *position);
extern void OffsetBoxByDelta_0203ac70(void *src, void *dst, void *delta);
extern void func_ov016_020a58a0(FieldObject *obj);
extern int func_ov016_020a57e8(FieldObject *obj);
extern void func_ov016_020a31f0(FieldObject *obj);
extern BOOL func_ov016_020a2b78(FieldObject *obj);
extern int func_ov016_020a393c(FieldObject *obj);
extern int func_ov016_020a40e0(FieldObject *obj);
extern void func_ov016_020a4210(FieldObject *obj);
extern void func_ov016_020a446c(FieldObject *obj);
extern void func_ov016_020a4800(FieldObject *obj);
extern void func_ov016_020a3c50(FieldObject *obj);
extern void func_ov016_020a57cc(FieldObject *obj);
extern void func_ov016_020a582c(FieldObject *obj);
extern void func_ov016_020a34fc(FieldObject *obj, int arg);
extern void func_ov016_020a27ac(FieldObject *obj);

int UpdateFieldObject_020a596c(FieldObject *obj)
{
    u32 flags = obj->flags;
    FieldActor *actor;
    BOOL finished;

    if (flags & 0x10) {
        return 0;
    }
    if (obj->state == 6) {
        func_ov016_020a58a0(obj);
        return 0;
    }
    if (!(flags & 0x100000)) {
        if (!(flags & 0x200000)) {
            actor = func_02036240(obj->actorId);
            if (actor->boxInitialized == 0) {
                actor->boxInitialized = 1;
                obj->position = actor->position;
                func_0203afa0(actor->point, &obj->position);
                OffsetBoxByDelta_0203ac70(actor->bounds, actor->movedBounds, actor->delta);
            }
            obj->lastPosition = obj->position;
            flags = obj->flags | 0x100000;
            obj->flags = flags;
            if (flags & 0x400000) {
                func_ov016_020a31f0(obj);
            }
            if (obj->timer != 0) {
                obj->timer -= 0x89;
                if (obj->timer < 0) {
                    obj->timer = 0;
                }
            }
            func_ov016_020a2b78(obj);
            switch (obj->state) {
            case 5:
                func_ov016_020a58a0(obj);
                return func_ov016_020a57e8(obj);
            case 1:
            case 2:
            case 3:
                return func_ov016_020a393c(obj);
            case 4:
                return func_ov016_020a40e0(obj);
            }
            switch (obj->mode) {
            case 5:
                func_ov016_020a4210(obj);
                break;
            case 6:
                func_ov016_020a446c(obj);
                break;
            case 7:
                func_ov016_020a4800(obj);
                break;
            case 11:
                func_ov016_020a3c50(obj);
                break;
            case 3:
                func_ov016_020a57cc(obj);
                break;
            }
            func_ov016_020a582c(obj);
            if (obj->mode == 9 || (u8)(obj->mode + 0xf4) <= 3) {
                finished = TRUE;
            } else {
                finished = FALSE;
            }
            if (finished) {
                func_ov016_020a34fc(obj, 0);
            }
        }
        func_ov016_020a27ac(obj);
    }
    return 0;
}
