#include "src/overlays/ov101/ListMenuData.h"

#pragma explicit_zero_data on

extern BOOL func_ov101_020beb40(ListSceneState *scene);
extern void ShutdownListScene(ListSceneState *scene);
extern void UpdateListScene(ListSceneState *scene);
extern void func_ov101_020bee4c(void);
extern void func_ov101_020befdc(void);
extern void func_ov101_020bf294(void);
extern void func_ov101_020bf16c(void);
extern void func_ov101_020bf3b0(void);
extern void ToggleListPage(void);
extern void func_ov101_020bf3d8(void);
ListSceneDescriptor gListSceneDescriptor = {
    func_ov101_020beb40, ShutdownListScene, UpdateListScene,
    9, 0xdc0c,
    {
        func_ov101_020bee4c, func_ov101_020befdc, func_ov101_020bf294,
        func_ov101_020bf16c, func_ov101_020bf16c, func_ov101_020bf3b0,
        ToggleListPage, NULL, NULL, NULL, NULL, func_ov101_020bf3d8,
    }
};
