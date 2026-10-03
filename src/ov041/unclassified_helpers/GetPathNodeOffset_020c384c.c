#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x4c];
    VecFx32 position;
} PathNode;

typedef struct {
    u8 pad_000[0x104];
    PathNode *nodes;
    int nodeIndex;
} PathFollower;

extern VecFx32 data_02053438;
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void GetPathNodeOffset_020c384c(PathFollower *follower, VecFx32 *out, VecFx32 *delta) {
    VecFx32 pos = follower->nodes[follower->nodeIndex].position;

    VEC_Subtract_01ff9e3c(&pos, &data_02053438, &pos);
    if (delta != NULL) {
        VEC_Subtract_01ff9e3c(&pos, out, delta);
    }
    *out = pos;
}
