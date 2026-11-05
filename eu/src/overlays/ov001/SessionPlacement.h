#ifndef KH_RECODED_SESSION_PLACEMENT_H
#define KH_RECODED_SESSION_PLACEMENT_H

#include "nitro/fx_types.h"

/* Three position words at packed bits 0x3537/0x3557/0x3577, then a 16-bit angle
 * at bit 0x3597. No allocation or implicit coordinate conversion occurs. */
void StorePackedSessionPlacement(const VecFx32 *position, u32 angle);
void LoadPackedSessionPlacement(VecFx32 *position, u16 *angle);

#endif
