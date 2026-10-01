#include "nitro/types.h"

typedef struct StageVector {
    s32 x;
    s32 y;
    s32 z;
} StageVector;

typedef struct StageManager {
    u8 pad_00000[0x18e60];
    StageVector vectors[1];
} StageManager;

typedef struct ScriptRecord {
    u8 pad_00[4];
    s32 index;
} ScriptRecord;

extern StageManager *func_ov001_0209c3c0(void);
extern u32 func_ov021_020b0374(u32 context, int operand);
extern s32 TaggedValueToFixed_020b03b0(u32 tagged);

u32 ScriptOp_SubtractStageVector_020b2178(u32 context, int operands)
{
    ScriptRecord *record = (ScriptRecord *)func_ov021_020b0374(context, operands);
    u32 xValue = func_ov021_020b0374(context, operands + 8);
    u32 yValue = func_ov021_020b0374(context, operands + 0x10);
    u32 zValue = func_ov021_020b0374(context, operands + 0x18);
    StageManager *manager = func_ov001_0209c3c0();

    manager->vectors[record->index].x -= TaggedValueToFixed_020b03b0(xValue);
    manager->vectors[record->index].y -= TaggedValueToFixed_020b03b0(yValue);
    manager->vectors[record->index].z -= TaggedValueToFixed_020b03b0(zValue);
    return 0;
}
