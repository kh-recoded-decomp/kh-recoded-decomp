#include "nitro/types.h"

typedef struct TargetCandidate {
    s32 object;
    u8 pad_04[0x10];
} TargetCandidate;

typedef struct TargetSearch {
    s32 bestDistance;
    s32 bestIndex;
    s32 unk_08;
} TargetSearch;

typedef struct Manager {
    u8 pad_00[0x4c];
    s32 searchRange;
} Manager;

extern Manager *g_manager_020a0484;
extern TargetCandidate *func_ov001_0206b930(TargetCandidate *candidate);
extern TargetSearch *func_ov001_0206ba18(TargetSearch *search);
extern void func_ov001_0206b434(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void func_ov001_0206b598(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void func_ov001_0206b744(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void func_ov001_0206b854(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);

BOOL FindNearestTargetInRange_0206af7c(TargetCandidate *result, void *origin)
{
    Manager *manager = g_manager_020a0484;
    BOOL found = FALSE;
    TargetCandidate candidate;
    TargetSearch search;

    func_ov001_0206b930(&candidate);
    func_ov001_0206ba18(&search);
    func_ov001_0206b434(&candidate, &search, origin, manager->searchRange);
    func_ov001_0206b598(&candidate, &search, origin, manager->searchRange);
    func_ov001_0206b744(&candidate, &search, origin, manager->searchRange);
    func_ov001_0206b854(&candidate, &search, origin, manager->searchRange);
    if (candidate.object != 0) {
        *result = candidate;
        found = TRUE;
    }
    return found;
}
