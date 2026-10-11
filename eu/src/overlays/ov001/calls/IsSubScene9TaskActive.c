#include "src/overlays/ov001/SceneTaskTables.h"

BOOL IsSubScene9TaskActive(void)
{
    if (gSubScene9TaskHandle != -1) {
        return TRUE;
    }
    return FALSE;
}
