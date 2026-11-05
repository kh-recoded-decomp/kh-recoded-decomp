#ifndef KH_RECODED_COLLISION_TRAVERSAL_H
#define KH_RECODED_COLLISION_TRAVERSAL_H

#include "nitro/types.h"

#define COLLISION_TRAVERSAL_DEPTH 8

/* The X/Z region is halved for each level of the quadtree traversal. */
typedef struct CollRegion {
    s32 centerX;
    s32 centerZ;
    s32 size;
} CollRegion;

typedef struct CollTraversalFrame {
    s16 childIndex;
    u16 nodeFlags;
    CollRegion region;
} CollTraversalFrame;

typedef char CollRegionSizeCheck[sizeof(CollRegion) == 0x0c ? 1 : -1];
typedef char CollTraversalFrameSizeCheck[sizeof(CollTraversalFrame) == 0x10 ? 1 : -1];
typedef char CollTraversalPointerSizeCheck[sizeof(void *) == 4 ? 1 : -1];

/* Shared DS workspace: these are not independent per-query stacks.
 * DTCM +0xb0 holds the cursor; +0xb4..+0x134 holds eight frames.
 */
extern CollTraversalFrame *gCollisionTraversalTop;
extern CollTraversalFrame gCollisionTraversalFrames[COLLISION_TRAVERSAL_DEPTH];

#endif
