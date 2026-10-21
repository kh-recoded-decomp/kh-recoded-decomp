#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern int ProjectWorldToScreenFx(const VecFx32 *world, StageScreenPoint *screen);

/*
 * Shows a marker of the given list at the screen position of a world point: takes the last free
 * marker, shows it with a 14-frame timer and returns it. Returns NULL when the point is off screen.
 */
StageMarker *ShowStageMarker(int listIndex, const VecFx32 *world, BOOL persistent)
{
    StageWork *work = gMovieContextState->stageWork;
    u8 slot = 0xff;
    StageScreenPoint screen;
    u8 i;

    if (ProjectWorldToScreenFx(world, &screen) != -1) {
        for (i = 0; i < work->markerLists[listIndex].count; i++) {
            if (!(work->markerLists[listIndex].markers[i].flags & STAGE_MARKER_IN_USE)) {
                slot = i;
            }
        }
        work->markerLists[listIndex].markers[slot].flags |= STAGE_MARKER_VISIBLE | STAGE_MARKER_IN_USE;
        work->markerLists[listIndex].markers[slot].timer = 14;
        work->markerLists[listIndex].markers[slot].screen = screen;
        if (persistent) {
            work->markerLists[listIndex].markers[slot].flags |= STAGE_MARKER_PERSISTENT;
        }
        return &work->markerLists[listIndex].markers[slot];
    }
    return NULL;
}
