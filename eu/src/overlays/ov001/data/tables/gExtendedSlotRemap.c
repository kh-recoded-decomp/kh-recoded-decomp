#include "src/overlays/ov001/StageActorTables.h"

/* Negative values retain the extended slot's own index. Last two bytes are padding. */
s8 gExtendedSlotRemap[32] = {
    -1, -1, -1, -1, -1, -1, -1, -1,
    33, 65, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 43, 44,
    45, -1, -1, -1, 34, 99, 0, 0
};
