#ifndef OV099_ENEMY_VIEWER_INFO_H
#define OV099_ENEMY_VIEWER_INFO_H

#include "nitro/types.h"

/* The name is read from the enemy-name message container. The defeat count
 * is stored as a 17-bit field starting at defeatCountBitOffset. */
typedef struct EnemyViewerEntryInfo {
    u32 messageId;
    u32 defeatCountBitOffset;
} EnemyViewerEntryInfo;

extern EnemyViewerEntryInfo gEnemyViewerEntryInfo[40];

#endif
