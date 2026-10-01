#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 type;
    int raw;
} ScriptOperand;

typedef struct TimerTarget {
    int value;
    s16 x;
    s16 y;
    s16 z;
    s16 range;
} TimerTarget;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern void func_ov001_02069370(int id, BOOL repeat, int unused, BOOL paused, BOOL silent, TimerTarget *target);

int ScriptOp_StartFieldTimerAt_020650e4(void *vm, ScriptOperand *operands)
{
    int repeat = ScriptVm_ReadOperandInt_02025de4(vm, &operands[0]);
    int id = ScriptVm_ReadOperandInt_02025de4(vm, &operands[1]);
    TimerTarget target;
    int paused;
    int silent;
    int packed;

    target.value = ScriptVm_ReadOperandInt_02025de4(vm, &operands[2]);
    paused = ScriptVm_ReadOperandInt_02025de4(vm, &operands[3]);
    silent = ScriptVm_ReadOperandInt_02025de4(vm, &operands[4]);
    packed = operands[5].raw;
    target.x = packed;
    target.y = packed >> 16;
    target.z = ScriptVm_ReadOperandInt_02025de4(vm, &operands[6]);
    target.range = ScriptVm_ReadOperandInt_02025de4(vm, &operands[7]);
    func_ov001_02069370(id, repeat != 0, 1, paused != 0, silent != 0, &target);
    return 1;
}
