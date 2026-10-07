#include "src/overlays/ov031/Ov031MovieState.h"

u32 SetNearestStageEvent(u32 eventId)
{
    gOv031MovieState->nearestEvent = (u16)eventId;
    return eventId;
}
