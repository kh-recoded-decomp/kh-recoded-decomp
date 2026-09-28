#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *script, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *script, ScriptOperand *operand);
extern void *func_ov007_020a1778(u16 objectId, s16 shortParameter, fx32 fxParameter, int entryCount);
extern void func_ov001_0207ee04(int slotIndex, void *object);

int ScriptCmd_CreateEntryObjectInSlot_020a0520(void *script, ScriptOperand *operands)
{
    int slotIndex = ScriptVm_ReadOperandInt_02025de4(script, operands);
    int objectId = ScriptVm_ReadOperandInt_02025de4(script, operands + 1);
    int shortParameter = ScriptVm_ReadOperandInt_02025de4(script, operands + 2);
    fx32 fxParameter = ScriptVm_ReadOperandFx32_02025df8(script, operands + 3);
    int entryCount = ScriptVm_ReadOperandInt_02025de4(script, operands + 4);

    func_ov001_0207ee04(slotIndex, func_ov007_020a1778((u16)objectId, (s16)shortParameter, fxParameter, entryCount));
    return 1;
}
