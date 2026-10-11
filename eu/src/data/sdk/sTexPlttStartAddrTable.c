#include "libs/nitro/os/os_types_internal.h"

/* Indexed by the E/F/G bank mask (GXVRamTexPltt >> 4).
 * Entries are LCDC addresses in 4 KB pages, expanded by << 12 on load. */
const u16 sTexPlttStartAddrTable[8] = {
    0x0000, 0x6880, 0x6890, 0x6880,
    0x6894, 0x0000, 0x6890, 0x6880,
};
