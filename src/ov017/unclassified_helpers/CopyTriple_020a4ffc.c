#include "nitro/types.h"

typedef struct Triple {
    u32 words[3];
} Triple;

void CopyTriple_020a4ffc(Triple *dest, Triple *src)
{
    *dest = *src;
}
