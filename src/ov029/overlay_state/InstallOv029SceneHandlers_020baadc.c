#include "nitro/types.h"

typedef void *SceneHandler;

typedef struct {
    SceneHandler states[9];
    u8 pad_24[4];
    SceneHandler onEnter;
} SceneHandlerTable;

extern void func_ov029_020ba9b0(int arg0);
extern BOOL func_ov029_020ba9d4(void);
extern u32 func_ov029_020baa00(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
extern u32 func_ov029_020baa24(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
extern BOOL HasOv029ObjectField28_020baa40(void);
extern void ReleaseOv029Object_020baa64(void);
extern void func_ov029_020baa84(void *params);
extern u32 func_ov029_020baacc(u32 argument0, u32 argument1, u32 argument2, u32 argument3);
extern void func_ov029_020ba86c(int mode);
extern u32 func_ov029_020baad4(u32 argument0, u32 argument1, u32 argument2, u32 argument3);

void InstallOv029SceneHandlers_020baadc(SceneHandlerTable *table) {
    table->states[0] = func_ov029_020ba9b0;
    table->states[1] = func_ov029_020ba9d4;
    table->states[2] = func_ov029_020baa00;
    table->states[3] = func_ov029_020baa24;
    table->states[4] = HasOv029ObjectField28_020baa40;
    table->states[5] = ReleaseOv029Object_020baa64;
    table->states[6] = func_ov029_020baa84;
    table->states[7] = func_ov029_020baacc;
    table->states[8] = func_ov029_020ba86c;
    table->onEnter = func_ov029_020baad4;
}
