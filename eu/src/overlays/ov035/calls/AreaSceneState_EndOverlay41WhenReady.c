#include "nitro/types.h"

extern void EndOverlay41Phase(void);
extern int UpdateStageFrame(void);

u32 AreaSceneState_EndOverlay41WhenReady(void) {
    if (UpdateStageFrame() != 0) {
        EndOverlay41Phase();
        return 7;
    }
    return 0xffffffff;
}
