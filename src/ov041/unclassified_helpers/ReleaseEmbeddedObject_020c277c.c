#include "nitro/types.h"

extern void ReleaseResourceAndDetach_0202eee8(void *node);

void ReleaseEmbeddedObject_020c277c(u8 *owner) {
    ReleaseResourceAndDetach_0202eee8(owner + 0x3a8);
}
