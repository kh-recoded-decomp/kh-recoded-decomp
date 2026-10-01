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
    u8 pad_28[0x0f];
    u8 attrByte;
    u32 flagLow : 1;
    u32 flagHigh : 1;
    u32 modelId : 10;
    u32 motionId : 10;
    u32 effectId : 10;
    u8 pad_3c[4];
    fx32 rangeMin;
    fx32 rangeMax;
    fx32 height;
    u32 soundId : 10;
    u32 soundParam : 12;
    u32 unk_4c_22 : 10;
} ScriptEntityParams;

extern void func_ov016_020a62dc(ScriptEntityParams *params);
extern s32 ScriptVm_ConsumeOperandInt_020a1de0(void *vm, ScriptOperand **cursor);
extern fx32 ScriptVm_ConsumeOperandFx32_020a1df4(void *vm, ScriptOperand **cursor);
extern int func_ov001_020644b0(void);
extern u32 func_ov032_020bb884(u32 modelId);

s32 ScriptCmd_ReadEntityParams_020a1e64(ScriptEntityParams *params, void *vm, ScriptOperand **cursorOut)
{
    ScriptOperand *cursor = *cursorOut;
    s32 result;
    u32 value;
    BOOL remap;

    func_ov016_020a62dc(params);
    result = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    params->entityId = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    params->groupId = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    value = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    params->kindHigh = (u16)(value >> 16);
    params->kind = (u16)value;
    params->posX = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    params->posY = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    params->posZ = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    value = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    params->flagHigh = value >> 28;
    params->flagLow = (value >> 24) & 0xf;
    params->attrByte = value >> 16;
    params->flagByte = value;
    value = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    params->modelId = value >> 20;
    params->effectId = value >> 10;
    params->motionId = value;
    remap = func_ov001_020644b0() == 900;
    if (remap) {
        params->modelId = func_ov032_020bb884(params->modelId);
    }
    value = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    params->soundId = (u16)(value >> 16);
    params->soundParam = value;
    if (params->modelId != 0 || params->effectId != 0 || params->soundId != 0) {
        params->extraLow = cursor->value;
        params->extraHigh = cursor->value >> 16;
        cursor++;
    }
    params->radius = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    params->height = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    if (params->kind == 2 || params->kind == 4) {
        params->kindParam = ScriptVm_ConsumeOperandInt_020a1de0(vm, &cursor);
    }
    if (params->kind == 3 || params->kind == 4) {
        params->rangeMin = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
        params->rangeMax = ScriptVm_ConsumeOperandFx32_020a1df4(vm, &cursor);
    }
    *cursorOut = cursor;
    return result;
}
