#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_000[0x50];
    int speakerId;
    u8 pad_054[0x74];
    char pendingText[0x108];
    BOOL hasPendingText;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
    u8 pad_1cc[0x45c];
    BOOL skipMessages;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern BOOL IsFieldPanelShown_02071860(void);
extern u32 func_ov001_0207a648(int speakerId);
extern BOOL SplitTextAtLineBreak_0208c4d8(char *text, char *dest);
extern int Utf8ToUcs2_020512b4(const char *src, u16 *dst, int maxChars);
extern void ShowMessageWindowMode1_02071a14(int speakerId, int mode, u16 *text, int flags);

int ScriptCmd_ShowSpeakerMessage_0208dadc(ScriptContext *context, ScriptOperand *operands)
{
    int speakerId = ScriptVm_ReadOperandInt_02025de4(context, &operands[0]);
    char *text;
    u16 wideText[256];

    ScriptVm_ReadOperandInt_02025de4(context, &operands[1]);
    text = func_02025dac(context, &operands[2]);
    if (context->skipMessages) {
        return 1;
    }
    if (!IsFieldPanelShown_02071860()) {
        return 0;
    }
    context->scene->speakerId = speakerId;
    if (func_ov001_0207a648(speakerId) == 0) {
        if (SplitTextAtLineBreak_0208c4d8(text, context->scene->pendingText)) {
            context->scene->hasPendingText = TRUE;
        }
        Utf8ToUcs2_020512b4(text, wideText, 256);
        ShowMessageWindowMode1_02071a14(context->scene->speakerId, 1, wideText, 0);
    }
    return 1;
}
