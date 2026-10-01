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
    u32 flags;
    TargetCandidate current;
    u8 pad_18[0x30];
    s32 lockRange;
} Manager;

extern Manager *g_manager_020a0484;
extern TargetCandidate *func_ov001_0206b930(TargetCandidate *candidate);
extern TargetSearch *func_ov001_0206ba18(TargetSearch *search);
extern void func_ov001_0206b434(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void func_ov001_0206b598(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void func_ov001_0206b744(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void func_ov001_0206b854(TargetCandidate *candidate, TargetSearch *search, void *origin, s32 range);
extern void func_ov001_0206bb74(int mode, int flag);

void SelectNearestTarget_0206afec(void)
{
    Manager *manager = g_manager_020a0484;
    TargetCandidate candidate;
    TargetSearch search;

    if (manager->flags & 1) {
        func_ov001_0206bb74(1, 1);
        return;
    }
    func_ov001_0206b930(&candidate);
    func_ov001_0206ba18(&search);
    func_ov001_0206b434(&candidate, &search, NULL, manager->lockRange);
    func_ov001_0206b598(&candidate, &search, NULL, manager->lockRange);
    func_ov001_0206b744(&candidate, &search, NULL, manager->lockRange);
    func_ov001_0206b854(&candidate, &search, NULL, manager->lockRange);
    if (candidate.object != 0) {
        manager->current = candidate;
        func_ov001_0206bb74(1, 1);
    }
}
