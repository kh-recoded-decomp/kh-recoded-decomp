#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageNode {
    struct StageNode *next;
} StageNode;

extern VecFx32 data_ov058_020d8a2c;

extern BOOL IsFirstEntryFlagSet_0206e584(void);
extern StageNode *func_ov001_0208723c(void);
extern VecFx32 *func_ov001_020863f4(StageNode *node);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);
extern void func_ov016_020a6d8c(StageNode *node, int arg);

void PurgeNearbyStageObjects_020d7998(void)
{
    VecFx32 *center = &data_ov058_020d8a2c;
    StageNode *node;
    VecFx32 *pos;
    fx32 delta;

    if (IsFirstEntryFlagSet_0206e584()) {
        return;
    }
    for (node = func_ov001_0208723c(); node != NULL; node = node->next) {
        pos = func_ov001_020863f4(node);
        if (pos == NULL) {
            continue;
        }
        delta = pos->x - center->x;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta >= 0x8000) {
            continue;
        }
        delta = pos->z - center->z;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta >= 0x8000) {
            continue;
        }
        delta = pos->y - center->y;
        if (delta < 0) {
            delta = -delta;
        }
        if (delta >= 0x8000) {
            continue;
        }
        if (func_01ffa0f4(pos, center) < 0x8000) {
            func_ov016_020a6d8c(node, 0);
        }
    }
}
