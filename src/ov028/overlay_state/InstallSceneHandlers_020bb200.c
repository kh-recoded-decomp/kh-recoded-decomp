#include "nitro/types.h"

typedef void *SceneHandler;

typedef struct {
    SceneHandler states[9];
    u8 pad_24[4];
    SceneHandler onEnter;
    SceneHandler onExit;
} SceneHandlerTable;

extern void func_ov028_020bafc8(int arg0);
extern BOOL func_ov028_020bafec(void);
extern u32 func_ov028_020bb018(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
extern void SetFieldModeFlag_020bb03c(u8 mode);
extern BOOL func_ov028_020bb060(void);
extern void ReleaseHandle_020bb084(void);
extern void SetupSceneFromParams_020bb0a4(void *params);
extern BOOL IsSceneUnpaused_020bb15c(void);
extern void func_ov028_020bae68(s32 mode);
extern u32 func_ov028_020bb17c(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
extern void func_ov028_020bb194(void);
extern BOOL func_ov001_020645c8(u32 value);
extern void ApplyAreaMusicEntry_02064734(int mode);

void InstallSceneHandlers_020bb200(SceneHandlerTable *table) {
    table->states[0] = func_ov028_020bafc8;
    table->states[1] = func_ov028_020bafec;
    table->states[2] = func_ov028_020bb018;
    table->states[3] = SetFieldModeFlag_020bb03c;
    table->states[4] = func_ov028_020bb060;
    table->states[5] = ReleaseHandle_020bb084;
    table->states[6] = SetupSceneFromParams_020bb0a4;
    table->states[7] = IsSceneUnpaused_020bb15c;
    table->states[8] = func_ov028_020bae68;
    table->onEnter = func_ov028_020bb17c;
    table->onExit = func_ov028_020bb194;
    ApplyAreaMusicEntry_02064734(func_ov001_020645c8(0x3ee4) ? 4 : 0);
}
