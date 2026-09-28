#include "nitro/types.h"

void *ResolveTaggedPointer_0200b034(int *value) {
    if (*((s8 *)value + 3) != 0) {
        value = (int *)*value;
    }
    return value;
}
