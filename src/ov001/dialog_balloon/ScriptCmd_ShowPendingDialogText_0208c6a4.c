#include "nitro/types.h"

typedef struct ScriptSceneData {
    u8 pad_000[0x50];
    void *balloon;
    u32 speakerId;
    u8 pad_058[0xc8 - 0x58];
    char pendingText[0x100];
    u8 pad_1c8[4];
    BOOL unk_1CC;
    BOOL balloonActive;
} ScriptSceneData;

typedef struct ScriptContext {
    u8 pad_000[0x1c8];
    ScriptSceneData *scene;
} ScriptContext;

extern u32 func_ov001_0207a648(void *operands);
extern u32 func_ov001_0207a810(void);
extern char *strcpy_02021e60(char *dst, const char *src);
extern BOOL SplitTextAtLineBreak_0208c4d8(char *text, char *dest);
extern int Utf8ToUcs2_020512b4(const char *src, u16 *dst, int maxChars);
extern void func_ov001_02071a14(void *balloon, int mode, u16 *text, int flags);
extern void func_ov001_0208c534(ScriptContext *context, u16 *text, u32 speakerId);
extern void WriteSessionPackedBits_0206459c(int bitOffset, u32 bitCount, u32 value);

int ScriptCmd_ShowPendingDialogText_0208c6a4(ScriptContext *context, void *operands)
{
    ScriptSceneData *scene;
    char lineText[0x100];
    u16 wideText[0x100];

    if (func_ov001_0207a648(operands) == 0) {
        scene = context->scene;
        if (scene->unk_1CC == 0 && scene->pendingText[0] != 0) {
            strcpy_02021e60(lineText, scene->pendingText);
            SplitTextAtLineBreak_0208c4d8(lineText, context->scene->pendingText);
            Utf8ToUcs2_020512b4(lineText, wideText, 0x100);
            scene = context->scene;
            if (scene->balloonActive != 0) {
                func_ov001_02071a14(scene->balloon, 1, wideText, 0);
            } else {
                func_ov001_0208c534(context, wideText, scene->speakerId);
            }
            return 0;
        }
        WriteSessionPackedBits_0206459c(0x3521, 4, func_ov001_0207a810());
        return 1;
    }
    return 0;
}
