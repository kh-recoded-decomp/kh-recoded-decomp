#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PathNode {
    u8 pad_00[0x18];
    s32 radius;
    s32 height;
    u8 pad_20[4];
    VecFx32 place;
} PathNode;

extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

BOOL IsPointInNodeRange_02069644(PathNode *node, const VecFx32 *point)
{
    VecFx32 place;
    VecFx32 target;
    s32 height;
    s32 offset;

    if ((node->radius & 0x80000000) != 0) {
        return TRUE;
    }

    offset = point->y - node->place.y;
    height = node->height;
    if (height > 0) {
        if (offset < 0 || offset > height) {
            return FALSE;
        }
    } else if (height < 0) {
        if (offset > 0 || offset < height) {
            return FALSE;
        }
    } else {
        return FALSE;
    }

    place = node->place;
    target = *point;
    place.y = 0;
    target.y = 0;
    if (func_01ffa0f4(&place, &target) <= node->radius) {
        return TRUE;
    }
    return FALSE;
}
