#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
} TargetSource;

typedef struct {
    u8 pad_00[0x24];
    VecFx32 *position;
} TargetNode;

typedef struct {
    u8 pad_000[0x10c];
    TargetNode node;
} TargetActor;

typedef struct {
    union {
        TargetSource *source;
        struct {
            u16 eventId;
            u16 slot;
        } event;
    } u;
    s32 kind;
} TargetKey;

extern const VecFx32 data_02053438;
extern TargetActor *func_02036240(int id);
extern int QueryStageEventPlacement_02087bec(u32 id, int arg, VecFx32 *position, u16 *direction);

void TargetKey_GetPosition_020cf0a4(VecFx32 *out, TargetKey *key)
{
    VecFx32 position;
    TargetNode *node;

    switch (key->kind) {
    case 1:
        node = &func_02036240(key->u.source->actorId)->node;
        *out = *node->position;
        break;
    case 2:
        QueryStageEventPlacement_02087bec(key->u.event.eventId, key->u.event.slot, &position, NULL);
        *out = position;
        break;
    default:
        *out = data_02053438;
        break;
    }
}
