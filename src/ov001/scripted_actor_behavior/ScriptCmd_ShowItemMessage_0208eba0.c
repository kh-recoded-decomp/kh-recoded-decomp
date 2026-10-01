#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptContext {
    u8 pad_000[0x628];
    int skipping;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern void PlaySoundChecked_0204d8d0(void *ptr, int arg);
extern int Utf8ToUcs2_020512b4(const char *src, u16 *dst, int maxChars);
extern BOOL IsFieldPanelShown_02071860(void);
extern void ShowMessageWindowMode3_02071a84(u16 *text);
extern u32 GetFieldHandle_0207365c(s32 handleIndex);
extern u16 *FormatWideText_0208c338(const u16 *format, u16 *dest, u32 destLength, ...);
extern void GrantRecordItem_0208c358(int itemId);
extern void func_ov001_0208c534(ScriptContext *context, u16 *text, int speaker);

int ScriptCmd_ShowItemMessage_0208eba0(ScriptContext *context, ScriptOperand *operands)
{
    u16 format[0x100];
    u16 formatted[0x100];
    int speaker = ScriptVm_ReadOperandInt_02025de4(context, operands);
    int kind = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    char *text = func_02025dac(context, operands + 2);
    int itemId = ScriptVm_ReadOperandInt_02025de4(context, operands + 3);

    if (context->skipping != 0) {
        if (kind == 1) {
            GrantRecordItem_0208c358(itemId);
        }
        return 1;
    }
    if (!IsFieldPanelShown_02071860()) {
        return 0;
    }
    Utf8ToUcs2_020512b4(text, format, 0x100);
    switch (kind) {
    case 0:
        FormatWideText_0208c338(format, formatted, 0x100, itemId);
        func_ov001_0208c534(context, formatted, speaker);
        break;
    case 1:
        FormatWideText_0208c338(format, formatted, 0x100, GetFieldHandle_0207365c(itemId));
        ShowMessageWindowMode3_02071a84(formatted);
        GrantRecordItem_0208c358(itemId);
        PlaySoundChecked_0204d8d0(0, 9);
        break;
    case 2:
        break;
    }
    return 1;
}
