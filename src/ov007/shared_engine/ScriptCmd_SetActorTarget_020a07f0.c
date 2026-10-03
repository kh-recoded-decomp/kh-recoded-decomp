#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, void *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, void *operand);
extern void *func_ov001_0207f038(int group, int index);
extern void SetTargetPosition_020a1b64(void *mover, const VecFx32 *target);

BOOL ScriptCmd_SetActorTarget_020a07f0(void *vm, u8 *cmd) {
    int group = ScriptVm_ReadOperandInt_02025de4(vm, cmd);
    int index = ScriptVm_ReadOperandInt_02025de4(vm, cmd + 8);
    VecFx32 target;

    target.x = ScriptVm_ReadOperandFx32_02025df8(vm, cmd + 0x10);
    target.y = ScriptVm_ReadOperandFx32_02025df8(vm, cmd + 0x18);
    target.z = ScriptVm_ReadOperandFx32_02025df8(vm, cmd + 0x20);
    SetTargetPosition_020a1b64(func_ov001_0207f038(group, index), &target);
    return TRUE;
}
