#include "src/overlays/ov039/RuntimeState.h"

int RuntimeState_GetObjectId(void)
{
    return RUNTIME_STATE_TAIL->objectId;
}
