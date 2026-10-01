#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

extern int ScriptVm_ReadOperandInt_02025de4(void *vm, ScriptOperand *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *vm, ScriptOperand *operand);
extern void *func_ov001_02087214(int tableIndex);
extern void func_ov017_020a271c(void *table, u16 objectId, int slot, u16 packedLow, u8 packedHigh, VecFx32 *position,
                                s8 sizeX, s8 sizeY, s8 sizeZ, fx32 param);

int func_ov020_020a1e10(void *vm, ScriptOperand *operands)
{
    int tableIndex = ScriptVm_ReadOperandInt_02025de4(vm, operands);
    int objectId = ScriptVm_ReadOperandInt_02025de4(vm, operands + 1);
    int slot = ScriptVm_ReadOperandInt_02025de4(vm, operands + 2);
    u32 packed = operands[3].value;
    VecFx32 position;
    fx32 param;
    int sizeX;
    int sizeY;
    int sizeZ;

    position.x = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 4);
    position.y = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 5);
    position.z = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 6);
    param = ScriptVm_ReadOperandFx32_02025df8(vm, operands + 7);
    sizeX = ScriptVm_ReadOperandInt_02025de4(vm, operands + 8);
    sizeY = ScriptVm_ReadOperandInt_02025de4(vm, operands + 9);
    sizeZ = ScriptVm_ReadOperandInt_02025de4(vm, operands + 10);

    func_ov017_020a271c(func_ov001_02087214(tableIndex), objectId, slot, packed, (u16)(packed >> 16), &position,
                        sizeX, sizeY, sizeZ, param);
    return 1;
}
