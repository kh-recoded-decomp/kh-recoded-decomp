#include "nitro/types.h"

#pragma define_section sha1RoundConstants ".text" ".text" ".text" RX

/* SHA-1's four round constants precede the block routine's PC-relative loads. */
__declspec(sha1RoundConstants) const u32 MATHi_SHA1RoundConstants[4] = {
    0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6
};
