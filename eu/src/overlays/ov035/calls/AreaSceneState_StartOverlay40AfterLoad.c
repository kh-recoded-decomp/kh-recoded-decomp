#include "nitro/types.h"

extern u32 gMovieContextState;
extern int StepResourceSlotLoading(void);
extern void InvokeSceneCallback(void);
extern void TriggerQueuedStageEventPairs(void);
extern void InvokeListNodeCallbacks(void);
extern void StartOverlay40Phase(int arg);

u32 AreaSceneState_StartOverlay40AfterLoad(void) {
    if (StepResourceSlotLoading() == 0) {
        return 0xffffffff;
    }
    InvokeSceneCallback();
    TriggerQueuedStageEventPairs();
    InvokeListNodeCallbacks();
    StartOverlay40Phase(1);
    *(u16 *)(gMovieContextState + 6) = *(u16 *)(gMovieContextState + 6) | 0x8000;
    return 4;
}
