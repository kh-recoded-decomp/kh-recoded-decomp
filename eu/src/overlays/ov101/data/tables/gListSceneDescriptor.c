#include "src/overlays/ov101/ListMenuData.h"

#pragma explicit_zero_data on

extern BOOL InitializeListScene(ListSceneState *scene);
extern void ShutdownListScene(ListSceneState *scene);
extern void UpdateListScene(ListSceneState *scene);
extern void HandleListUpInput(void);
extern void HandleListDownInput(void);
extern void HandleListLeftInput(void);
extern void HandleListRightInput(void);
extern void ListScene_ReturnToParentMenu(void);
extern void ToggleListPage(void);
extern void ListScene_ReturnToRootMenu(void);
ListSceneDescriptor gListSceneDescriptor = {
    InitializeListScene, ShutdownListScene, UpdateListScene,
    9, 0xdc0c,
    {
        HandleListUpInput, HandleListDownInput, HandleListLeftInput,
        HandleListRightInput, HandleListRightInput, ListScene_ReturnToParentMenu,
        ToggleListPage, NULL, NULL, NULL, NULL, ListScene_ReturnToRootMenu,
    }
};
