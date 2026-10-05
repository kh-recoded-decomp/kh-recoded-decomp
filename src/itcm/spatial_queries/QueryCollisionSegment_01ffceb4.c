#include "nitro/types.h"

typedef struct CollisionQueryInfo {
    const void *start;
    const void *end;
    u32 resultFlags;
    u16 enabled;
    u8 pad[0x60 - 0xe];
} CollisionQueryInfo;

extern void *func_020351b8(void *scene, CollisionQueryInfo *info);

void QueryCollisionSegment_01ffceb4(void *scene, const void *start, const void *end) {
    CollisionQueryInfo info;
    info.start = start;
    info.end = end;
    info.enabled = 1;
    func_020351b8(scene, &info);
}
