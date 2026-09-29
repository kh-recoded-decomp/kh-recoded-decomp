#include "nitro/types.h"

typedef struct CollHitRecord {
    u32 words[0x2e];
} CollHitRecord;

typedef struct CollTraversalFrame CollTraversalFrame;
typedef struct CollWorld CollWorld;

extern void func_01ff878c(const void *src, void *dest, u32 size);
extern CollHitRecord *CollWorld_FindHit_020351cc(CollWorld *world, const void *params);
extern CollHitRecord g_collHitRecord_027e0134;
extern CollHitRecord data_02060784;
extern u8 data_027e00b4[0x80];
extern CollTraversalFrame *data_027e00b0;

CollHitRecord *CollWorld_FindHitPreserveState_02034ab4(CollWorld *world, const void *params)
{
    u8 savedFrames[0x80];
    CollHitRecord result;
    CollTraversalFrame *savedTop;
    CollHitRecord *hit;

    data_02060784 = g_collHitRecord_027e0134;
    func_01ff878c(data_027e00b4, savedFrames, sizeof(savedFrames));
    savedTop = data_027e00b0;
    hit = CollWorld_FindHit_020351cc(world, params);
    if (hit != NULL) {
        result = *hit;
    }
    g_collHitRecord_027e0134 = data_02060784;
    func_01ff878c(savedFrames, data_027e00b4, sizeof(savedFrames));
    data_027e00b0 = savedTop;
    if (hit != NULL) {
        data_02060784 = result;
        return &data_02060784;
    }
    return NULL;
}
