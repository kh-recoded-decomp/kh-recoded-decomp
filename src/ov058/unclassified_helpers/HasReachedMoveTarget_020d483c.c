#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 kind;
    u8 pad_01[3];
    u16 eventId;
    u16 slot;
} MoveTarget;

typedef struct {
    s32 mode;
    u32 flags;
} AiState;

typedef struct {
    u8 pad_0000[0x1048];
    MoveTarget target;
    u8 pad_1050[0x1258 - 0x1050];
    AiState ai;
} Enemy;

typedef struct {
    u8 data[0x24];
} EventTargetInfo;

typedef struct {
    VecFx32 position;
    fx32 radius;
    u8 pad_10[4];
} SlotPoint;

extern VecFx32 *func_ov052_020ceb54(Enemy *enemy);
extern BOOL GetStageEventTargetInfo_02087960(u32 id, EventTargetInfo *out);
extern BOOL StageRecord_GetSlotPosition_02087c4c(u32 id, u32 slot, SlotPoint *outPoint);
extern fx32 func_01ffa0f4(const VecFx32 *a, const VecFx32 *b);

BOOL HasReachedMoveTarget_020d483c(Enemy *enemy, const VecFx32 *dest)
{
    BOOL reached = FALSE;
    AiState *ai = &enemy->ai;
    MoveTarget *target = &enemy->target;
    VecFx32 pos = *func_ov052_020ceb54(enemy);
    VecFx32 goal = *dest;
    EventTargetInfo info;
    SlotPoint point;
    fx32 dist;

    switch (enemy->target.kind) {
    case 1:
        if (ai->flags & 0x1000) {
            reached = TRUE;
            break;
        }
        goal.y = 0;
        pos.y = 0;
        if (!GetStageEventTargetInfo_02087960(target->eventId, &info)) {
            break;
        }
        if (!StageRecord_GetSlotPosition_02087c4c(target->eventId, target->slot, &point)) {
            break;
        }
        dist = func_01ffa0f4(&pos, &goal);
        if (dist < point.radius + 0xccd || dist <= 0x2333) {
            reached = TRUE;
        }
        break;
    case 2:
        goal.y = 0;
        pos.y = 0;
        if (func_01ffa0f4(&pos, &goal) < 0x2000) {
            reached = TRUE;
        }
        break;
    case 3:
        goal.y = 0;
        pos.y = 0;
        if (func_01ffa0f4(&pos, &goal) < 0x2000) {
            reached = TRUE;
        }
        break;
    }
    return reached;
}
