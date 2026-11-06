#include "nitro/types.h"

extern void FinishPoolActions(void);

void *const gKind4PoolTriggerHitHandlers[5] = {
    NULL,
    NULL,
    NULL,
    NULL,
    (void *)FinishPoolActions,
};
