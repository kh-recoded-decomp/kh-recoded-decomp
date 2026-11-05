#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void InitCounterHudWork(void);
extern void ReleaseCounterHudWork(void);

StageManagerTaskDescriptor gFieldHudStatusTaskDescriptor = {
    0x000e0016,
    (void *)InitCounterHudWork,
    (void *)ReleaseCounterHudWork,
    0x910,
    NULL,
};
