#include "src/overlays/ov001/StageActorTables.h"

#pragma explicit_zero_data on

extern void *InitFieldMenu(u32 *parameters);
extern void DestroyFieldMenu(void);

StageManagerTaskDescriptor gFieldMenuTaskDescriptor = {
    0x000e000b,
    (void *)InitFieldMenu,
    (void *)DestroyFieldMenu,
    0x150,
    NULL,
};
