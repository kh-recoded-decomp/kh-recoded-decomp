#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x16];
    u16 motionId;
} StageActor;

typedef struct {
    u8 pad_00[0x2c0];
    VecFx32 position;
} StageTarget;

typedef struct {
    StageActor *actor;
    u32 pad_04;
    StageTarget *target;
} StageGlobals;

typedef struct {
    u8 pad_00[0x2c];
    u16 hasResult;
    u16 pad_2e;
    s32 result;
} ScriptContext;

extern StageGlobals data_ov021_020b56a4;
extern void *GetStageMotionRecord_0209c18c(u16 motionId);
extern void func_ov001_02091c34(StageTarget *target, VecFx32 *out);
extern int GetGridCellIndex_020a12d4(void *grid, VecFx32 *position);
extern BOOL IsGridLineClear_020a139c(void *grid, int fromCell, int toCell);

int ScriptCmd_CheckTargetLineOfSight_020b0eec(ScriptContext *context)
{
    StageActor *actor = data_ov021_020b56a4.actor;
    StageTarget *target;
    void *grid;
    int fromCell;
    int toCell;
    VecFx32 targetPos;

    if (actor == NULL) {
        return 0;
    }
    target = data_ov021_020b56a4.target;
    if (target == NULL) {
        return 0;
    }
    grid = GetStageMotionRecord_0209c18c(actor->motionId);
    if (grid == NULL) {
        return 0;
    }
    if (grid == NULL) {
        return 0;
    }
    if (actor == NULL) {
        return 0;
    }
    if (target == NULL) {
        return 0;
    }
    func_ov001_02091c34(target, &targetPos);
    fromCell = GetGridCellIndex_020a12d4(grid, &target->position);
    toCell = GetGridCellIndex_020a12d4(grid, &targetPos);
    context->hasResult = 1;
    context->result = IsGridLineClear_020a139c(grid, fromCell, toCell);
    return 0;
}
