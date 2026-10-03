#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScriptOperand {
    u32 type;
    u32 value;
} ScriptOperand;

typedef struct ScriptEntityParams {
    s32 entityId;
    s32 groupId;
    u16 extraLow;
    u8 extraHigh;
    u8 flagByte;
    u32 kindHigh;
    u32 kind;
    s32 kindParam;
    fx32 posX;
    fx32 posY;
    fx32 posZ;
    fx32 radius;
    u8 pad_28[0x0c];
    u8 colorR;
    u8 colorG;
    u8 colorB;
    u8 attrByte;
    u8 pad_38[0x5c - 0x38];
} ScriptEntityParams;

extern s32 ScriptCmd_ReadEntityParams_020a1e64(ScriptEntityParams *params, void *vm, ScriptOperand **cursorOut);
extern s32 ScriptVm_ConsumeOperandInt_020a1de0(void *vm, ScriptOperand **cursor);
extern void func_ov016_020a2064(ScriptEntityParams *params, void *vm, ScriptOperand **cursor);
extern unsigned int func_ov001_02087214(int index);
extern void func_ov016_020a6338(unsigned int group, ScriptEntityParams *params);

BOOL ScriptCmd_ApplyEntityColorVecParams_020a20c0(void *vm, ScriptOperand *operands)
{
    ScriptOperand *cursor = operands;
    ScriptEntityParams params;
    s32 index;
    u32 color;

    index = ScriptCmd_ReadEntityParams_020a1e64(&params, vm, &cursor);
    color = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    params.colorR = color >> 16;
    params.colorG = color >> 8;
    params.colorB = color;
    func_ov016_020a2064(&params, vm, &cursor);
    func_ov016_020a6338(func_ov001_02087214(index), &params);
    return TRUE;
}
