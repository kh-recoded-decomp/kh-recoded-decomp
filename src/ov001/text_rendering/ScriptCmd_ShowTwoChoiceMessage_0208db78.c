#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScriptSceneData {
    u8 pad_00[0x50];
    s32 windowId;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

typedef struct ChoiceWindowParams {
    int mode;
    int count;
    u16 **choices;
    int flags;
} ChoiceWindowParams;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern char *func_02025dac(ScriptContext *context, ScriptOperand *operand);
extern int IsFieldPanelShown_02071860(void);
extern u32 func_ov001_0207a648(int windowId);
extern int Utf8ToUcs2_020512b4(const char *src, u16 *dst, int maxChars);
extern void ShowMessageWindowMode1_02071a14(int x, int y, void *arg, void *flags);

int ScriptCmd_ShowTwoChoiceMessage_0208db78(ScriptContext *context, ScriptOperand *operands)
{
    int windowId;
    char *text;
    char *choiceA;
    char *choiceB;
    u16 *choices[2];
    ChoiceWindowParams params;
    u16 wideText[0x100];
    u16 choiceAText[0x40];
    u16 choiceBText[0x40];

    windowId = ScriptVm_ReadOperandInt_02025de4(context, operands);
    ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    text = func_02025dac(context, operands + 2);
    choiceA = func_02025dac(context, operands + 3);
    choiceB = func_02025dac(context, operands + 4);
    if (IsFieldPanelShown_02071860() == 0) {
        return 0;
    }
    context->scene->windowId = windowId;
    if (func_ov001_0207a648(windowId) == 0) {
        choices[0] = choiceAText;
        choices[1] = choiceBText;
        params.mode = 2;
        params.count = 1;
        params.flags = 0;
        Utf8ToUcs2_020512b4(text, wideText, 0x100);
        Utf8ToUcs2_020512b4(choiceA, choices[0], 0x40);
        Utf8ToUcs2_020512b4(choiceB, choices[1], 0x40);
        params.choices = choices;
        ShowMessageWindowMode1_02071a14(context->scene->windowId, 1, wideText, &params);
    }
    return 1;
}
