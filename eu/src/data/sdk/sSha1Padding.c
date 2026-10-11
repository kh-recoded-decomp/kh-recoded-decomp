#include "nitro/types.h"

/* SHA-1 finalization first appends 0x80, then uses the zero-byte view at +1.
 * The original allocation includes eleven zero bytes. */
const u8 sSha1Padding[12] = { 0x80 };
