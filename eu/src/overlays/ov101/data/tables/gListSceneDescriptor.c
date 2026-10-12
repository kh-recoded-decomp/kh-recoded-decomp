#include "src/overlays/ov101/ListMenuData.h"

#pragma explicit_zero_data on

extern BOOL InitializeListScene(ListSceneState *scene);
extern void ShutdownListScene(ListSceneState *scene);
extern void UpdateListScene(ListSceneState *scene);
extern void HandleListUpInput(void);
extern void HandleListDownInput(void);
extern void HandleListLeftInput(void);
extern void HandleListRightInput(void);
extern void func_ov101_020bf3b0(void);
extern void ToggleListPage(void);
extern void func_ov101_020bf3d8(void);
ListSceneDescriptor gListSceneDescriptor = {
    InitializeListScene, ShutdownListScene, UpdateListScene,
    9, 0xdc0c,
    {
        HandleListUpInput, HandleListDownInput, HandleListLeftInput,
        HandleListRightInput, HandleListRightInput, func_ov101_020bf3b0,
        ToggleListPage, NULL, NULL, NULL, NULL, func_ov101_020bf3d8,
    }
};
