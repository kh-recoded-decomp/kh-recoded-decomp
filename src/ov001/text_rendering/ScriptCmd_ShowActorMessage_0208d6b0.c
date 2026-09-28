#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_00[0x54];
    s32 speakerId;
    u8 pad_58[0xc8 - 0x58];
    char pendingLine[0x100];
    u8 pad_1c8[0x1d0 - 0x1c8];
    s32 unk_1D0;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
    u8 pad_1cc[0x628 - 0x1cc];
    s32 isSkipping;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int func_ov001_02071860(void);
extern BOOL SplitTextAtLineBreak_0208c4d8(char *text, char *dest);
extern int Utf8ToUcs2_020512b4(const char *src, u16 *dst, int maxChars);
extern void func_ov001_0208c534(ScriptContext *context, u16 *text, int speakerId);

int ScriptCmd_ShowActorMessage_0208d6b0(ScriptContext *context, ScriptOperand *operands)
{
    int speakerId;
    char *text;
    u16 wideText[0x200];

    speakerId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    text = func_02025dac(context, operands + 1);
    if (context->isSkipping != 0) {
        return 1;
    }
    if (func_ov001_02071860() == 0) {
        return 0;
    }
    if (SplitTextAtLineBreak_0208c4d8(text, context->scene->pendingLine) != 0) {
        context->scene->speakerId = speakerId;
        context->scene->unk_1D0 = 0;
    }
    Utf8ToUcs2_020512b4(text, wideText, 0x200);
    func_ov001_0208c534(context, wideText, speakerId);
    return 1;
}
