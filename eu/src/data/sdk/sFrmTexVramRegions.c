#include "libs/nitro/os/os_types_internal.h"

typedef struct NNSGfdFrmTexRegionState {
    u32 head;
    u32 tail;
    BOOL bActive;
    const BOOL bHalfSize;
    const u16 index;
    const u16 pad16_;
    const u32 baseAddress;
} NNSGfdFrmTexRegionState;

typedef char FrmTexRegionMustBe24Bytes[sizeof(NNSGfdFrmTexRegionState) == 24 ? 1 : -1];

/* Consecutive entries of the allocator's five-region table. Keep an exported
 * name at each entry because the search lists also address entries directly.
 * Regions 1 and 2 are the half-size index banks for compressed 4x4 textures.
 */
NNSGfdFrmTexRegionState sFrmTexVramRegions[1] = {
    { 0xffffffff, 0xffffffff, 0, 0, 0, 0xffff, 0x00000 }
};
NNSGfdFrmTexRegionState sFrmTexVramRegion1 = {
    0xffffffff, 0xffffffff, 0, 1, 1, 0xffff, 0x20000
};
NNSGfdFrmTexRegionState sFrmTexVramRegion2 = {
    0xffffffff, 0xffffffff, 0, 1, 2, 0xffff, 0x30000
};
NNSGfdFrmTexRegionState sFrmTexVramRegion3 = {
    0xffffffff, 0xffffffff, 0, 0, 3, 0xffff, 0x40000
};
NNSGfdFrmTexRegionState sFrmTexVramRegion4 = {
    0xffffffff, 0xffffffff, 0, 0, 4, 0xffff, 0x60000
};
