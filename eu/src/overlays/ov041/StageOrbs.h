#ifndef STAGE_ORBS_H
#define STAGE_ORBS_H

#include "nitro/types.h"
#include "nitro/fx.h"

/* StageOrb.phase */
#define STAGE_ORB_BURST 0 /* thrown out, falling */
#define STAGE_ORB_HOMING 1 /* flying at its collector */
#define STAGE_ORB_FREE 2

#define STAGE_ORB_COUNT 0x80

/* A recovery orb: it bursts out of a defeated entry, then homes in on the entry that collects it. */
typedef struct StageOrb {
    int phase;
    VecFx32 velocity;
    fx32 value; /* hp it restores, fx32 */
    u32 link[2]; /* in StageOrbPool.drawList while it flies */
    void *sprite;
    VecFx32 position;
    s16 scale;
    s16 baseScale;
    u8 frame;
    u8 frameTimer;
    u8 width;
    u8 height;
    s16 alpha;
    s16 rotation;
} StageOrb;

typedef struct StageOrbPool {
    StageOrb orbs[STAGE_ORB_COUNT];
    u8 drawList[0x1d0]; /* a draw manager; its list of flying orbs is at +0x10 */
    u8 sprite[4];
} StageOrbPool;

typedef char StageOrbSize[sizeof(StageOrb) == 0x38 ? 1 : -1];

#endif
