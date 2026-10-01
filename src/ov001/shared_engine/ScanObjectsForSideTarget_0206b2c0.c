#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct TargetObject {
    struct TargetObject *next;
} TargetObject;

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
extern TargetObject *func_ov001_0208723c(void);
extern BOOL func_ov001_0206b614(void *origin, TargetObject *object, s32 range);
extern VecFx32 *func_ov001_020863f4(TargetObject *object);
extern BOOL CheckSideOffsetInRange_0206b3d4(const VecFx32 *position, const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset);
extern TargetCandidate *func_ov001_0206b940(TargetCandidate *candidate, TargetObject *object);

BOOL ScanObjectsForSideTarget_0206b2c0(const VecFx32 *facing, fx32 low, fx32 high, s32 direction, fx32 *outOffset)
{
    Manager *manager = g_manager_020a0484;
    BOOL found = FALSE;
    TargetObject *object;

    if (!(manager->flags & 0x40)) {
        return found;
    }
    for (object = func_ov001_0208723c(); object != NULL; object = object->next) {
        if (func_ov001_0206b614(NULL, object, manager->lockRange) &&
            CheckSideOffsetInRange_0206b3d4(func_ov001_020863f4(object), facing, low, high, direction, outOffset)) {
            func_ov001_0206b940(&manager->current, object);
            high = *outOffset;
            found = TRUE;
        }
    }
    return found;
}
