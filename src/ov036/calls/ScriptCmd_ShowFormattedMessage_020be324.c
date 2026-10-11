#include "nitro/types.h"
#pragma opt_propagation off
#pragma opt_common_subs off

typedef struct ScriptContext {
    u8 reserved[0x628];
    int isSkipping;
} ScriptContext;

typedef struct ScriptOperand {
    s16 type;
    u16 parameter02;
    u32 value;
} ScriptOperand;

extern const char *ByteCode_ResolveOperand_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern int Utf8ToUcs2_020512b4(const char *source, u16 *dest, int capacity);
extern void CopyRecordTableAString_020be2f4(int record, u16 *dest);
extern u16 *func_ov036_020be2d4(const u16 *format, u16 *dest, u32 capacity, ...);
extern BOOL OpenMessageTextWindowAlt_020c3024(const u16 *text);
extern void PlaySoundChecked_0204d8d0(int group, int sound);

int ScriptCmd_ShowFormattedMessage_020be324(ScriptContext *context, ScriptOperand *operands)
{
    u16 format[256];
    u16 output[256];
    u16 value[64];
    u32 capacity;
    u16 *formatBuffer;
    u16 *valueBuffer;
    const char *text = ByteCode_ResolveOperand_02025dac(context, operands);
    if (context->isSkipping != 0) {
        return 1;
    }
    formatBuffer = format;
    capacity = 256;
    Utf8ToUcs2_020512b4(text, formatBuffer, capacity);
    if (operands[1].type == 1) {
        int record = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
        valueBuffer = value;
        CopyRecordTableAString_020be2f4(record, valueBuffer);
    } else {
        text = ByteCode_ResolveOperand_02025dac(context, operands + 1);
        valueBuffer = value;
        Utf8ToUcs2_020512b4(text, valueBuffer, 64);
    }
    func_ov036_020be2d4(formatBuffer, output, capacity, valueBuffer);
    OpenMessageTextWindowAlt_020c3024(output);
    PlaySoundChecked_0204d8d0(0, 9);
    return 1;
}
