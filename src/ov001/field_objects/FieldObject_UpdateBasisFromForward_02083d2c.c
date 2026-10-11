#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct {
    VecFx32 right;
    VecFx32 up;
    VecFx32 forward;
} Basis;

typedef struct {
    u16 flags;
    u8 pad_02[0x7e];
    Basis basis;
} ActorState;

typedef struct {
    u8 pad_00[0x14];
    ActorState state;
} FieldObjectWork;

typedef struct {
    u8 pad_00[0xc];
    FieldObjectWork *work;
    u8 pad_10[0x54];
    VecFx32 forward;
    VecFx32 up;
} FieldObject;

extern void BuildBasisFromForward_0204bf70(const VecFx32 *forward, const VecFx32 *up, Basis *out);

static inline void ApplyBasis(FieldObject *object, const Basis *basis)
{
    ActorState *state;

    object->up = basis->up;
    state = &object->work->state;
    state->basis = *basis;
    state->flags &= ~0x20;
}

void FieldObject_UpdateBasisFromForward_02083d2c(FieldObject *object)
{
    Basis basis;
    Basis built;
    Basis result;

    BuildBasisFromForward_0204bf70(&object->forward, &object->up, &built);
    result = built;
    *(MtxFx33 *)&basis = *(MtxFx33 *)&result;
    ApplyBasis(object, &basis);
}
