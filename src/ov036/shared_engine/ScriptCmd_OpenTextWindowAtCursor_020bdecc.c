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

typedef struct PanelPoint {
    s32 x;
    s32 y;
} PanelPoint;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern const char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern void func_01ff86fc(u32 data, void *dest, u32 size);
extern int Utf8ToUcs2Bounded_020bda5c(const char *src, u16 *dst, int dstCount);
extern BOOL GetPanelCursorOverride_020bda08(s32 *outSelection, PanelPoint *outPosition);
extern void func_ov036_020bdc04(ScriptContext *context, ScriptOperand *textOperand, int windowId, s32 selection, PanelPoint *position);
extern void func_ov036_020c2f0c(int windowId, s32 selection, PanelPoint *position, int style, u16 *text);

int ScriptCmd_OpenTextWindowAtCursor_020bdecc(ScriptContext *context, ScriptOperand *operands)
{
    ScriptOperand *op = operands;
    ScriptOperand *textOperand;
    const char *utf8;
    int windowId;
    PanelPoint position;
    s32 selection;
    int style;
    u16 text[0x100];

    ScriptVm_ReadOperandInt_02025de4(context, op++);
    textOperand = op;
    utf8 = func_02025dac(context, op++);
    windowId = ScriptVm_ReadOperandInt_02025de4(context, op++);
    selection = ScriptVm_ReadOperandInt_02025de4(context, op++);
    style = ScriptVm_ReadOperandInt_02025de4(context, op++);
    position.x = ScriptVm_ReadOperandInt_02025de4(context, op++);
    position.y = ScriptVm_ReadOperandInt_02025de4(context, op++);
    if (context->isSkipping != 0) {
        return 1;
    }
    func_01ff86fc(0, text, sizeof(text));
    Utf8ToUcs2Bounded_020bda5c(utf8, text, 0x100);
    if (!GetPanelCursorOverride_020bda08(&selection, &position)) {
        func_ov036_020bdc04(context, textOperand, windowId, selection, &position);
    }
    func_ov036_020c2f0c(windowId, selection, &position, style, text);
    return 1;
}
