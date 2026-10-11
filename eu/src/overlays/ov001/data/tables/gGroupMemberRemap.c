#include "src/overlays/ov001/StageActorTables.h"

/* A negative mapping selects the corresponding extended slot. Two trailing padding bytes. */
s8 gGroupMemberRemap[72] = {
    -1, 1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, 78, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, 92, 93, 94, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, 78, 78, -1, 61, 62, 63,
    -1, 79, 66, 67, 68, 69, 0, 0
};
