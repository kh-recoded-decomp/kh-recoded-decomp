#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int ScriptVm_ReadOperandInt_02025de4(void *scriptContext, u8 *operand);
extern fx32 ScriptVm_ReadOperandFx32_02025df8(void *scriptContext, u8 *operand);
extern int func_02025dac(void *scriptContext, u8 *operand);
extern void *func_ov001_0207f028(int index);
extern void *func_ov001_0208137c(void *objectClass, u16 slotIndex, u16 saveBitOffset, u8 saveBitCount,
                                 VecFx32 *position, u16 angle, int configFlags, int eventLabel,
                                 int scriptName, fx32 radius, int enabled, u8 layer);

int ScriptCmd_SpawnFieldObject_0207fda4(void *scriptContext, u8 *operands) {
    VecFx32 position;
    int configFlags;
    u16 saveBitOffset;
    u8 saveBitCount;
    int angle;
    int classIndex;
    int slotIndex;
    u32 packed;
    int eventLabel;
    int scriptName;
    fx32 radius;
    int enabled;
    int layer;

    classIndex = ScriptVm_ReadOperandInt_02025de4(scriptContext, operands);
    slotIndex = ScriptVm_ReadOperandInt_02025de4(scriptContext, operands + 0x08);
    packed = *(u32 *)(operands + 0x14);
    saveBitOffset = (u16)packed;
    saveBitCount = (u8)(u16)(packed >> 16);
    position.x = ScriptVm_ReadOperandFx32_02025df8(scriptContext, operands + 0x18);
    position.y = ScriptVm_ReadOperandFx32_02025df8(scriptContext, operands + 0x20);
    position.z = ScriptVm_ReadOperandFx32_02025df8(scriptContext, operands + 0x28);
    angle = (u16)((ScriptVm_ReadOperandInt_02025de4(scriptContext, operands + 0x30) << 16) / 360);
    configFlags = (s8)ScriptVm_ReadOperandInt_02025de4(scriptContext, operands + 0x38);
    if (*(s16 *)(operands + 0x40) == 0) {
        eventLabel = 0;
    } else {
        eventLabel = func_02025dac(scriptContext, operands + 0x40);
    }
    if (*(s16 *)(operands + 0x48) == 0) {
        scriptName = 0;
    } else {
        scriptName = func_02025dac(scriptContext, operands + 0x48);
    }
    radius = ScriptVm_ReadOperandFx32_02025df8(scriptContext, operands + 0x50);
    enabled = ScriptVm_ReadOperandInt_02025de4(scriptContext, operands + 0x58) != 0;
    layer = ScriptVm_ReadOperandInt_02025de4(scriptContext, operands + 0x60);
    func_ov001_0208137c(func_ov001_0207f028(classIndex), slotIndex, saveBitOffset, saveBitCount, &position,
                        angle, configFlags, eventLabel, scriptName, radius, enabled, layer);
    return 1;
}
