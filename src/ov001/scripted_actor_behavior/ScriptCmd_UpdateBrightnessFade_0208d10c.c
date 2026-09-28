#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct BrightnessFade {
    int startLevel;
    int endLevel;
    int duration;
    int currentLevel;
    int elapsed;
} BrightnessFade;

typedef struct ScriptSceneData {
    u8 pad_00[0x10];
    BrightnessFade fades[2];
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
    u8 pad_1CC[0x628 - 0x1cc];
    int skipRequested;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern int func_02023dbc(int dividend, int divisor);

int ScriptCmd_UpdateBrightnessFade_0208d10c(ScriptContext *context, ScriptOperand *operands, int screen)
{
    BrightnessFade *fade;
    int start;
    int elapsed;

    fade = &context->scene->fades[screen];
    if (context->skipRequested != 0) {
        fade->currentLevel = ScriptVm_ReadOperandInt_02025de4(context, operands) - 0x10;
        return 1;
    }
    elapsed = ++fade->elapsed;
    start = fade->startLevel;
    fade->currentLevel = start + func_02023dbc(elapsed * (fade->endLevel - start), fade->duration);
    if (fade->currentLevel > 0x10) {
        fade->currentLevel = 0x10;
    }
    if (fade->currentLevel < -0x10) {
        fade->currentLevel = -0x10;
    }
    if (screen == 0) {
        SetBrightnessAndSyncMain_02029e7c(fade->currentLevel);
    } else {
        SetSecondaryBrightness_02029ed0(fade->currentLevel);
    }
    if (fade->elapsed >= fade->duration) {
        return 1;
    }
    return 0;
}
