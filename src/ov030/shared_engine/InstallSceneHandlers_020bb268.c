#include "nitro/types.h"

typedef int (*SceneHandler)(void);

typedef struct {
    SceneHandler states[9];
    u8 pad_24[4];
    SceneHandler onEnter;
    SceneHandler onExit;
} SceneHandlerTable;

extern int func_ov030_020baba8(void);
extern int func_ov030_020babc0(void);
extern int func_ov030_020babdc(void);
extern int func_ov030_020babf4(void);
extern int func_ov030_020bac0c(void);
extern int func_ov030_020bac28(void);
extern int func_ov030_020bac48(void);
extern int IsSceneUnpaused_020bacb4(void);
extern int ApplyOverlayScaleMode_020baab4(void);
extern int func_ov030_020bb210(void);
extern int func_ov030_020bb220(void);
extern void func_ov001_02064734(int mode);

void InstallSceneHandlers_020bb268(SceneHandlerTable *table) {
    table->states[0] = func_ov030_020baba8;
    table->states[1] = func_ov030_020babc0;
    table->states[2] = func_ov030_020babdc;
    table->states[3] = func_ov030_020babf4;
    table->states[4] = func_ov030_020bac0c;
    table->states[5] = func_ov030_020bac28;
    table->states[6] = func_ov030_020bac48;
    table->states[7] = IsSceneUnpaused_020bacb4;
    table->states[8] = ApplyOverlayScaleMode_020baab4;
    table->onEnter = func_ov030_020bb210;
    table->onExit = func_ov030_020bb220;
    func_ov001_02064734(1);
}
