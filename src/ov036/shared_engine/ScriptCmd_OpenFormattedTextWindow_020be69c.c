#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x628];
    s32 isSkipping;
} ScriptContext;

typedef struct ScreenPoint {
    s32 x;
    s32 y;
} ScreenPoint;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern const char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int Utf8ToUcs2_020512b4(const char *src, u16 *dst, int maxChars);
extern u16 *func_ov036_020be2d4(const u16 *format, u16 *dest, u32 destLength, ...);
extern BOOL GetPanelCursorOverride_020bda08(s32 *outSelection, ScreenPoint *outPosition);
extern void func_ov036_020bdc04(ScriptContext *context, ScriptOperand *textOperand, int windowId, s32 selection, ScreenPoint *position);
extern BOOL OpenTextWindowWithText_020c2f0c(int windowId, s32 selection, ScreenPoint *position, int style, const u16 *text);

int ScriptCmd_OpenFormattedTextWindow_020be69c(ScriptContext *context, ScriptOperand *operands)
{
    ScriptOperand *op = operands;
    ScriptOperand *textOperand;
    const char *utf8;
    int windowId;
    ScreenPoint position;
    s32 selection;
    int style;
    int value;
    u16 format[0x100];
    u16 text[0x100];

    ScriptVm_ReadOperandInt_02025de4(context, op++);
    textOperand = op;
    utf8 = func_02025dac(context, op++);
    windowId = ScriptVm_ReadOperandInt_02025de4(context, op++);
    selection = ScriptVm_ReadOperandInt_02025de4(context, op++);
    style = ScriptVm_ReadOperandInt_02025de4(context, op++);
    if (context->isSkipping != 0) {
        return 1;
    }
    position.x = ScriptVm_ReadOperandInt_02025de4(context, op++);
    position.y = ScriptVm_ReadOperandInt_02025de4(context, op++);
    value = ScriptVm_ReadOperandInt_02025de4(context, op++);
    Utf8ToUcs2_020512b4(utf8, format, 0x100);
    func_ov036_020be2d4(format, text, 0x100, value);
    if (!GetPanelCursorOverride_020bda08(&selection, &position)) {
        func_ov036_020bdc04(context, textOperand, windowId, selection, &position);
    }
    OpenTextWindowWithText_020c2f0c(windowId, selection, &position, style, text);
    return 1;
}
