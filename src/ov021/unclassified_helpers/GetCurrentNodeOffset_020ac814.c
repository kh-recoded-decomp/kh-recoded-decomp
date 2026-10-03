#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x4c];
    VecFx32 position;
} PathNode;

typedef struct {
    u8 pad_000[0x104];
    PathNode *nodes;
    s32 nodeIndex;
} PathFollower;

extern const VecFx32 data_02053438;
extern void VEC_Subtract_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *ab);

void GetCurrentNodeOffset_020ac814(PathFollower *follower, VecFx32 *out, VecFx32 *delta)
{
    VecFx32 position = follower->nodes[follower->nodeIndex].position;

    VEC_Subtract_01ff9e3c(&position, &data_02053438, &position);
    if (delta != NULL) {
        VEC_Subtract_01ff9e3c(&position, out, delta);
    }
    *out = position;
}
