#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    u32 value;
} ScriptOperand;

typedef struct ScriptContext ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern BOOL GetPageVariantParams_020649d0(u32 index, u32 *outValue, u32 *outParamA, u32 *outParamB, BOOL usePrimary);
extern void WriteSessionPackedBits_0206459c(u16 bitOffset, u8 bitCount, u32 value);

BOOL ScriptCmd_StorePageVariantParams_02065cf4(ScriptContext *context, ScriptOperand *operands)
{
    u16 valueOffset;
    u16 paramAOffset;
    u16 paramBOffset;
    u8 valueCount;
    u8 paramACount;
    u8 paramBCount;
    BOOL usePrimary;
    u32 value;
    u32 paramA;
    u32 paramB;

    usePrimary = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    valueOffset = operands[1].value;
    valueCount = (u16)(operands[1].value >> 16);
    paramAOffset = operands[2].value;
    paramACount = (u16)(operands[2].value >> 16);
    paramBOffset = operands[3].value;
    paramBCount = (u16)(operands[3].value >> 16);

    if (!GetPageVariantParams_020649d0(ScriptVm_ReadOperandInt_02025de4(context, &operands[4]), &value, &paramA, &paramB,
                                       usePrimary)) {
        value = 0;
        paramA = 0;
        paramB = 0;
    }
    WriteSessionPackedBits_0206459c(valueOffset, valueCount, value);
    WriteSessionPackedBits_0206459c(paramAOffset, paramACount, paramA);
    WriteSessionPackedBits_0206459c(paramBOffset, paramBCount, paramB);
    return TRUE;
}
