#include "nitro/types.h"
#include "src/overlays/ov041/StageResources.h"

/* Frees a marker: drops its persistent flag, then all flags and the timer. */
void ReleaseStageMarker(StageMarker *marker)
{
    marker->flags &= (u8)~STAGE_MARKER_PERSISTENT;
    marker->flags = 0;
    marker->timer = 0;
}
