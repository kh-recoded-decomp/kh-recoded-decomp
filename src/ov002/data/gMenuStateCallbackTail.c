#include "nitro/types.h"

extern void CloseMenuElement5_020651c0(void);
extern void CloseMenuPopup(void);
extern void EnterMenuFadeOutState(void);
extern void EnterMenuFadeInState(void);
extern void OpenMenuPopup(void);
extern void OpenMenuSelector(void);
extern void ReleaseMenuPanelCallback(void);
extern void ResetMenuElement5_02065074(void);
extern void RunMenuIntroStep_02064ff8(void);
extern void UpdateMenuTouchSelect_020650e0(void);
extern void UpdateQuitMenuState(void);
extern void UpdateSaveMenuState(void);
extern void LeaveMenuIntroState(void);
extern void UpdateMenuFadeOutState(void);
extern void LeaveMenuFadeOutState(void);
extern void UpdateMenuFadeInState(void);
extern void LeaveMenuFadeInState(void);

void (*gMenuStateCallbackTail[16])(void) = {
    LeaveMenuIntroState,
    ResetMenuElement5_02065074,
    UpdateMenuTouchSelect_020650e0,
    CloseMenuElement5_020651c0,
    OpenMenuSelector,
    UpdateSaveMenuState,
    CloseMenuPopup,
    OpenMenuPopup,
    UpdateQuitMenuState,
    ReleaseMenuPanelCallback,
    EnterMenuFadeOutState,
    UpdateMenuFadeOutState,
    LeaveMenuFadeOutState,
    EnterMenuFadeInState,
    UpdateMenuFadeInState,
    LeaveMenuFadeInState,
};

void (*gMenuIntroUpdateCallback[1])(void) = {
    RunMenuIntroStep_02064ff8,
};
