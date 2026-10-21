#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

extern int ProjectWorldToScreenFx(const VecFx32 *world, StageScreenPoint *screen);

/* Keeps the marker's screen position when the world point projects onto the screen. */
void UpdateMarkerScreenPosition(StageMarker *marker, const VecFx32 *world)
{
    StageScreenPoint screen;

    if (ProjectWorldToScreenFx(world, &screen) != -1) {
        marker->screen = screen;
    }
}
