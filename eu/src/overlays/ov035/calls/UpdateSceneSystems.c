#include "nitro/types.h"

extern unsigned int gMovieContextState;
extern unsigned int ActorRegistry_ForEachCallback(void *);
extern unsigned int AdvanceLoopingAnimation(unsigned int);
extern unsigned int StageManager_Update(unsigned int);
extern unsigned int UpdatePrizeOrbs(void);
extern unsigned int func_020bd17c(unsigned int);
extern unsigned int UpdateSceneAnimsAndCaption(unsigned int);
extern unsigned int UpdatePartyEntries(unsigned int);
extern unsigned int GetManagedActorCount(void);
extern unsigned int UpdateFieldObjectStates(unsigned int);
extern unsigned int GetCurrentAreaIndex(void);
extern unsigned int GetOverlay41PhaseActiveFlag(void);
extern unsigned int UpdateMaterialFades(unsigned int, unsigned int);

void UpdateSceneSystems(int paused)
{
    int result;
    u32 step;
    int work;

    work = gMovieContextState;
    if ((*(u16 *)(gMovieContextState + 0x24) & 0x100) != 0) {
        AdvanceLoopingAnimation(0x1000);
    }
    if (paused == 0) {
        if ((*(u16 *)(work + 0x24) & 1) != 0) {
            UpdateSceneAnimsAndCaption(0x1000);
        }
        if ((*(u16 *)(work + 0x24) & 2) != 0) {
            UpdateFieldObjectStates(0x1000);
        }
        if ((*(u16 *)(work + 0x24) & 4) != 0) {
            result = GetCurrentAreaIndex();
            UpdateMaterialFades(result, 0x1000);
        }
    }
    step = GetManagedActorCount();
    if (0 < (int)step) {
        if ((*(u16 *)(work + 0x24) & 8) != 0) {
            UpdatePartyEntries(0x1000);
        }
    }
    if (paused == 0) {
        step = 0x1000;
        result = GetOverlay41PhaseActiveFlag();
        if ((result != 0) || ((*(u16 *)(work + 0x24) & 0x10) == 0)) {
            step = 0;
        }
        StageManager_Update(step);
        if ((*(u16 *)(work + 0x24) & 0x20) != 0) {
            UpdatePrizeOrbs();
        }
    }
    if ((*(u16 *)(work + 0x24) & 0x40) != 0) {
        ActorRegistry_ForEachCallback((void *)0x1000);
    }
    work = GetOverlay41PhaseActiveFlag();
    if (work != 0) {
        func_020bd17c(*(unsigned int *)(*(int *)(gMovieContextState + 0xb8) + 9000));
    }
}
