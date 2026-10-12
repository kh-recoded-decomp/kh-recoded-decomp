#include "src/overlays/ov001/HudGaugeTable.h"

/* Mutable: resizing the first HUD gauge updates its cell count. */
HudGaugeTable gHudGaugeTable = {
    -1,
    {
        {0x820, 0x1c0, 30},
        {0xa20, 0x60, 22},
        {0xa80, 0x60, 22}
    }
};
