#include "nitro/types.h"

typedef struct ScriptOperand {
    s16 type;
    s16 pad_02;
    s32 value;
} ScriptOperand;

typedef struct ScreenFade {
    s32 startLevel;
    s32 targetLevel;
    s32 duration;
    s32 currentLevel;
    s32 elapsed;
} ScreenFade;

typedef struct ScriptSceneData {
    u8 pad_00[0x10];
    ScreenFade fades[2];
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
    u8 pad_1cc[0x628 - 0x1cc];
    s32 isSkipping;
} ScriptContext;

extern int ScriptVm_ReadOperandInt_02025de4(ScriptContext *context, ScriptOperand *operand);
extern int func_02029f48(void);
extern int func_02029f58(void);
extern void SetBrightnessAndSyncMain_02029e7c(int value);
extern void SetSecondaryBrightness_02029ed0(int value);
extern void func_02006748(u16 *reg, int value);

void ScriptCmd_StartScreenBrightnessFade_0208d084(ScriptContext *context, ScriptOperand *operands, int screen)
{
    ScreenFade *fade;
    int duration;
    int level;

    fade = &context->scene->fades[screen];
    if (context->isSkipping != 0) {
        fade->currentLevel = ScriptVm_ReadOperandInt_02025de4(context, operands) - 16;
        return;
    }
    fade->elapsed = 0;
    fade->targetLevel = ScriptVm_ReadOperandInt_02025de4(context, operands) - 16;
    duration = ScriptVm_ReadOperandInt_02025de4(context, operands + 1);
    fade->duration = duration;
    fade->currentLevel = fade->targetLevel;
    if (duration > 0) {
        if (screen == 0) {
            level = func_02029f48();
        } else {
            level = func_02029f58();
        }
        fade->currentLevel = level;
        fade->startLevel = level;
    }
    if (screen == 0) {
        SetBrightnessAndSyncMain_02029e7c(fade->currentLevel);
        func_02006748((u16 *)0x0400006c, fade->currentLevel);
        return;
    }
    SetSecondaryBrightness_02029ed0(fade->currentLevel);
    func_02006748((u16 *)0x0400106c, fade->currentLevel);
}
