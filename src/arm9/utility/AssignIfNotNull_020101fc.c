#include "nitro/types.h"

void AssignIfNotNull_020101fc(u32 value, u32 *out)
{
    if (out != NULL) {
        *out = value;
    }
}
