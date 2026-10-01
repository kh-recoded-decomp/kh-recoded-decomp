#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TargetObject {
    u8 pad_00[0x3b];
    u8 lowFlags : 4;
    u8 category : 4;
} TargetObject;

typedef struct TargetRef {
    u8 kind;
    u8 pad_01[3];
    TargetObject *object;
} TargetRef;

typedef struct LockOnActor LockOnActor;
typedef int (*StateQueryFunc)(LockOnActor *actor);

struct LockOnActor {
    u8 pad_0000[0x1dc];
    int state;
    u8 pad_01e0[0x22c - 0x1e0];
    StateQueryFunc queryState;
    u8 pad_0230[0x1048 - 0x230];
    TargetRef target;
};

extern BOOL func_ov001_0206c3a4(TargetRef *target);
extern VecFx32 *func_ov001_0206c3f4(TargetRef *target);

BOOL QueryTargetPosition_020cc068(LockOnActor *actor, VecFx32 *outPosition)
{
    TargetRef *target;
    BOOL result;
    int state;

    target = &actor->target;
    result = FALSE;

    if (actor->queryState != NULL) {
        state = actor->queryState(actor);
    } else {
        state = actor->state;
    }
    if (state == 11) {
        return FALSE;
    }
    if (func_ov001_0206c3a4(target)) {
        result = TRUE;
        switch (actor->target.kind) {
        case 2:
            if (target->object->category == 1) {
                result = FALSE;
            }
            break;
        case 4:
            result = FALSE;
            break;
        }
        if (outPosition != NULL) {
            *outPosition = *func_ov001_0206c3f4(target);
        }
    }
    return result;
}
