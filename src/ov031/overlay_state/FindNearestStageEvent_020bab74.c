#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x5c];
    u16 nearestEvent;
} OverlayState;

extern OverlayState *g_activeState_020bc800;
extern VecFx32 *func_ov001_0206dc4c(int index);
extern u16 func_ov001_02087928(void);
extern u16 func_ov001_02087944(u16 id);
extern BOOL IsStageEventReady_02087c78(u16 id);
extern int QueryStageEventPlacement_02087bec(u16 id, int arg, VecFx32 *position, u16 *direction);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

void FindNearestStageEvent_020bab74(void)
{
    VecFx32 *origin = func_ov001_0206dc4c(0);
    fx32 best = 0x7fffffff;
    u16 id;
    u16 next;
    u16 prev;
    VecFx32 position;
    fx32 distance;
    int found;

    g_activeState_020bc800->nearestEvent = 0xffff;
    for (id = func_ov001_02087928(); id != 0; id = func_ov001_02087944(id)) {
        if (IsStageEventReady_02087c78(id)) {
            prev = 0;
            found = QueryStageEventPlacement_02087bec(id, 0, &position, &next);
            while (found) {
                distance = func_01ffa0f4(&position, origin);
                if (best > distance) {
                    best = distance;
                    g_activeState_020bc800->nearestEvent = id;
                }
                if (prev >= next) {
                    break;
                }
                prev = next;
                found = QueryStageEventPlacement_02087bec(id, next, &position, &next);
            }
        }
    }
}


