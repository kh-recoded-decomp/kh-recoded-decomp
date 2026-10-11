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

extern const char *ByteCode_ResolveOperand(ScriptContext *context, ScriptOperand *operand);
extern int ScriptVm_ReadOperandInt(ScriptContext *context, ScriptOperand *operand);
extern int Utf8ToUcs2(const char *source, u16 *dest, int capacity);
extern void CopyRecordTableAString(int record, u16 *dest);
extern u16 *func_ov036_020be2f4(const u16 *format, u16 *dest, u32 capacity, ...);
extern BOOL OpenMessageTextWindowAlt(const u16 *text);
extern void PlaySoundChecked(int group, int sound);

int ScriptCmd_ShowFormattedMessage(ScriptContext *context, ScriptOperand *operands)
{
    u16 format[256];
    u16 output[256];
    u16 value[64];
    u32 capacity;
    u16 *formatBuffer;
    u16 *valueBuffer;
    const char *text = ByteCode_ResolveOperand(context, operands);
    if (context->isSkipping != 0) {
        return 1;
    }
    formatBuffer = format;
    capacity = 256;
    Utf8ToUcs2(text, formatBuffer, capacity);
    if (operands[1].type == 1) {
        int record = ScriptVm_ReadOperandInt(context, operands + 1);
        valueBuffer = value;
        CopyRecordTableAString(record, valueBuffer);
    } else {
        text = ByteCode_ResolveOperand(context, operands + 1);
        valueBuffer = value;
        Utf8ToUcs2(text, valueBuffer, 64);
    }
    func_ov036_020be2f4(formatBuffer, output, capacity, valueBuffer);
    OpenMessageTextWindowAlt(output);
    PlaySoundChecked(0, 9);
    return 1;
}
