#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TargetActor {
    u8 pad_00[4];
    struct TargetActor *next;
} TargetActor;

typedef struct TargetCandidate {
    s32 kind;
    void *object;
    u8 pad_08[0xc];
} TargetCandidate;

typedef struct Manager {
    u32 flags;
    TargetCandidate current;
    u8 pad_18[0x30];
    s32 lockRange;
} Manager;

extern Manager *g_manager_020a0484;
extern TargetActor *func_ov001_0207f08c(void);
extern BOOL func_ov001_0206b4a4(void *origin, TargetActor *actor, s32 range);
extern VecFx32 *func_ov001_0207f870(TargetActor *actor);
extern BOOL CheckSideOffsetInRange_0206b3d4(const VecFx32 *position, const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);
extern TargetCandidate *func_ov001_0206b938(TargetCandidate *candidate, TargetActor *actor);

BOOL ScanActorsForSideTarget_0206b25c(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset)
{
    Manager *manager = g_manager_020a0484;
    BOOL found = FALSE;
    TargetActor *actor;

    for (actor = func_ov001_0207f08c(); actor != NULL; actor = actor->next) {
        if (func_ov001_0206b4a4(NULL, actor, manager->lockRange) &&
            CheckSideOffsetInRange_0206b3d4(func_ov001_0207f870(actor), facing, low, high, direction, outOffset)) {
            func_ov001_0206b938(&manager->current, actor);
            high = *outOffset;
            found = TRUE;
        }
    }
    return found;
}
