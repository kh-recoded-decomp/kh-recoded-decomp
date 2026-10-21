#include "nitro/types.h"
#include "src/overlays/ov041/StageWork.h"

extern void ReleaseStageMarker(StageMarker *marker);

/* Frees the markers shown for the current command. */
void ReleaseCommandMarkers(void)
{
    StageWork *work = gMovieContextState->stageWork;
    int i;

    for (i = 0; i < 9; i++) {
        if (work->commandMarkers[i] != NULL) {
            ReleaseStageMarker(work->commandMarkers[i]);
            work->commandMarkers[i] = NULL;
        }
    }
}
