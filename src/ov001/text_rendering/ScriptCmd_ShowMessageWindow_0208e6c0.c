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

extern char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern u32 func_ov001_02064574(u32 id, u32 bitCount);
extern BOOL func_ov001_020645c8(u32 flagId);
extern int func_ov001_02071860(void);
extern int Utf8ToUcs2_020512b4(const char *src, u16 *dst, int maxChars);
extern void func_ov001_02071a38(u16 *text, int windowStyle);

int ScriptCmd_ShowMessageWindow_0208e6c0(ScriptContext *context, ScriptOperand *operands)
{
    char *text;
    int windowStyle;
    u32 progress;
    u16 wideText[0x200];

    text = func_02025dac(context, operands);
    windowStyle = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    if (context->isSkipping != 0) {
        return 1;
    }
    progress = func_ov001_02064574(0x1a00, 2);
    if ((progress == 1 || progress == 3) && func_ov001_020645c8(0x363d) == 0) {
        return 1;
    }
    if (func_ov001_02071860() == 0) {
        return 0;
    }
    Utf8ToUcs2_020512b4(text, wideText, 0x200);
    func_ov001_02071a38(wideText, windowStyle);
    return 1;
}
