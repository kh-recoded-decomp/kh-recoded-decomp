#include "nitro/types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct {
    u8 high;
    u8 low;
    u16 middle;
    s32 param;
} OverlayLoadArgs;

extern s32 ScriptVm_ConsumeOperandInt_020a1de0(void *vm, ScriptOperand **cursor);
extern int DispatchOverlayLoadByKind_02086e90(u32 kind, int slot, u32 id, OverlayLoadArgs *args);
extern void func_ov001_02086f90(int index, int entry);

BOOL ScriptCmd_LoadOverlayKind9_020a1e08(void *vm, ScriptOperand *operands)
{
    ScriptOperand *cursor = operands;
    OverlayLoadArgs args;
    int slot;
    u32 id;
    s32 packed;

    slot = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    id = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    packed = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    args.low = packed;
    args.param = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    args.high = packed >> 24;
    args.middle = (u8)(packed >> 8);
    func_ov001_02086f90(slot, DispatchOverlayLoadByKind_02086e90(9, slot, id, &args));
    return TRUE;
}
