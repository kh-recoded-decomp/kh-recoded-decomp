#ifndef EU_STAGE_MANAGER_FLAGS_H
#define EU_STAGE_MANAGER_FLAGS_H

#include "nitro/types.h"

/* Return the selected bits, not a normalized boolean; return zero if absent. */
u32 GetMaskedStageManagerFlags(u32 mask);
/* OR/AND-not updates; neither replaces the complete flag word.
 * An absent stage manager makes either operation return without access.
 */
void SetStageManagerFlagBits(u32 mask);
void ClearStageManagerFlagBits(u32 mask);
/* If bit 0 is clear, clear mask 0x30 and return 3; otherwise return 0.
 * A missing stage manager follows the clear-bit path. No allocation occurs.
 */
int ClearStageMask30WhenBit0Clear(void);

#endif
