#include "nitro/types.h"

extern void AreaSceneState_LoadInitialResources(void);
extern void LoadShadowModelAndReturnState2(void);
extern void AreaSceneState_WaitForListNodes(void);
extern void AreaSceneState_StartOverlay40AfterLoad(void);
extern void PollOverlay40Phase(void); /* PollOverlay40Phase */
extern void FinishMovieSkip(void); /* FinishMovieSkip */
extern void AreaSceneState_EndOverlay41WhenReady(void);
extern void AreaSceneState_StartOverlay40Mode0(void);
extern void AreaSceneState_ReleaseResourcesAndExit(void);
extern void FinishMovieContextState(void);

void (*gMovieSkipHandlers[10])(void) = {
    AreaSceneState_LoadInitialResources,
    LoadShadowModelAndReturnState2,
    AreaSceneState_WaitForListNodes,
    AreaSceneState_StartOverlay40AfterLoad,
    PollOverlay40Phase, /* PollOverlay40Phase */
    FinishMovieSkip, /* FinishMovieSkip */
    AreaSceneState_EndOverlay41WhenReady,
    AreaSceneState_StartOverlay40Mode0,
    AreaSceneState_ReleaseResourcesAndExit,
    FinishMovieContextState,
};
