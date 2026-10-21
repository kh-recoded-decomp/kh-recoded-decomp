#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern void func_ov001_0206ad1c(StageMarker *marker);

/* Each frame: draws every shown marker and counts its timer down (persistent ones keep theirs); frees it at zero. */
void UpdateStageMarkers(void)
{
    StageWork *work = gMovieContextState->stageWork;
    int listIndex;
    int i;

    for (listIndex = 0; listIndex < 4; listIndex++) {
        for (i = 0; i < work->markerLists[listIndex].count; i++) {
            StageMarker *markers = work->markerLists[listIndex].markers;

            if (markers[i].flags & STAGE_MARKER_VISIBLE) {
                if (markers[i].timer != 0) {
                    func_ov001_0206ad1c(&markers[i]);
                    if (!(markers[i].flags & STAGE_MARKER_PERSISTENT)) {
                        markers[i].timer--;
                    }
                } else {
                    markers[i].flags &= (u8)~STAGE_MARKER_VISIBLE;
                    markers[i].flags &= (u8)~STAGE_MARKER_IN_USE;
                    markers[i].flags = 0;
                }
            }
        }
    }
}
