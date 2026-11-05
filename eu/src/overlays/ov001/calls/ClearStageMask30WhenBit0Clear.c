#include "src/overlays/ov001/StageManagerFlags.h"

int ClearStageMask30WhenBit0Clear(void)
{
    if (GetMaskedStageManagerFlags(1) == 0) {
        ClearStageManagerFlagBits(0x30);
        return 3;
    }
    return 0;
}
