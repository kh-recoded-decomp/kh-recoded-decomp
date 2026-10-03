#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotPosition {
    fx32 x;
    fx32 y;
} SlotPosition;

typedef struct ScreenPoint {
    s32 x;
    s32 y;
} ScreenPoint;

extern SlotPosition GetActorSlotPosition_020bd0dc(int actorId);

void GetActorBalloonAnchor_020bdda8(ScreenPoint *outPoint, int actorId)
{
    SlotPosition position = GetActorSlotPosition_020bd0dc(actorId);
    ScreenPoint point;

    point.x = (position.x >> 12) < 0x80 ? 0x6c : 0x94;
    if ((position.y >> 12) <= 0x80) {
        point.y = 0x19;
    } else {
        point.y = 0xa7;
    }
    *outPoint = point;
}
