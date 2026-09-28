#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 payload;
} ScriptOperand;

extern s32 ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern void *func_ov011_020a0fa4(u16 spawnParam);
extern void func_ov001_0207ee04(s32 slotIndex, void *actor);

BOOL ScriptCmd_SpawnActorInSlot_020a0560(void *vm, ScriptOperand *operands) {
    s32 slotIndex = ScriptVm_ReadOperandInt_02025de4(vm, &operands[0]);
    u16 spawnParam = ScriptVm_ReadOperandInt_02025de4(vm, &operands[1]);
    func_ov001_0207ee04(slotIndex, func_ov011_020a0fa4(spawnParam));
    return TRUE;
}
