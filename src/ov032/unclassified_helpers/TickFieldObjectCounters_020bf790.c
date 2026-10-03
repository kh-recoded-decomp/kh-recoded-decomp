#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u32 unk_00_0 : 9;
    u32 ownerIndex : 9;
    u32 unk_00_18 : 14;
    u32 unk_04_0 : 8;
    u32 cooldown : 8;
    u32 unk_04_16 : 16;
    u32 unk_08_0 : 6;
    u32 stunCount : 10;
    u32 unk_08_16 : 6;
    u32 lockCount : 10;
    u8 pad_0c[0x1d4];
} FieldObject;

typedef struct {
    u8 pad_00[0xcc];
    FieldObject *objects;
} FieldContext;

typedef struct {
    u8 pad_00[0x30];
    fx32 speed;
} HopState;

extern void *func_ov001_0208635c(FieldContext *context, int index);
extern HopState *func_ov032_020bbc78(void *object);
extern void func_ov032_020bbc3c(FieldObject *object, HopState *state);
extern void func_ov032_020bc5ec(FieldContext *context, int index);
extern void func_ov032_020bbf84(FieldContext *context, int index);
extern void AdvanceRowCounter_020bd440(FieldContext *context, int index);

void TickFieldObjectCounters_020bf790(FieldContext *context, int index)
{
    FieldObject *object = &context->objects[index];

    if (object->cooldown != 0) {
        object->cooldown--;
    }
    if (object->stunCount != 0) {
        HopState *state = func_ov032_020bbc78(func_ov001_0208635c(context, object->ownerIndex));
        object->stunCount--;
        if (object->stunCount == 0 && state->speed == 0) {
            func_ov032_020bbc3c(object, state);
        }
    }
    if (object->lockCount != 0) {
        object->lockCount--;
    }
    func_ov032_020bc5ec(context, index);
    func_ov032_020bbf84(context, index);
    AdvanceRowCounter_020bd440(context, index);
}
