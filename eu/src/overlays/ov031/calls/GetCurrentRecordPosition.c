#include "src/overlays/ov031/Ov031MovieState.h"

u32 GetCurrentRecordPosition(void)
{
    return gOv031MovieState->records[gOv031MovieState->recordIndex].position;
}
