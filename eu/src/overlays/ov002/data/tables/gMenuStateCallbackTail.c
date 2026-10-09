#include "nitro/types.h"

extern void LeaveMenuIntroState(void);
extern void ResetMenuElement5(void); /* ResetMenuElement5 */
extern void UpdateMenuTouchSelect(void); /* UpdateMenuTouchSelect */
extern void CloseMenuElement5(void); /* CloseMenuElement5 */
extern void OpenMenuSelector(void); /* OpenMenuSelector */
extern void UpdateSaveMenuState(void); /* UpdateSaveMenuState */
extern void CloseMenuPopup(void); /* CloseMenuPopup */
extern void OpenMenuPopup(void); /* OpenMenuPopup */
extern void UpdateQuitMenuState(void); /* UpdateQuitMenuState */
extern void ReleaseMenuPanelCallback(void); /* ReleaseMenuPanelCallback */
extern void EnterMenuFadeOutState(void);
extern void UpdateMenuFadeOutState(void);
extern void LeaveMenuFadeOutState(void);
extern void EnterMenuFadeInState(void);
extern void UpdateMenuFadeInState(void);
extern void LeaveMenuFadeInState(void);
extern void RunMenuIntroStep(void); /* RunMenuIntroStep */

void (*gMenuStateCallbackTail[16])(void) = {
    LeaveMenuIntroState,
    ResetMenuElement5, /* ResetMenuElement5 */
    UpdateMenuTouchSelect, /* UpdateMenuTouchSelect */
    CloseMenuElement5, /* CloseMenuElement5 */
    OpenMenuSelector, /* OpenMenuSelector */
    UpdateSaveMenuState, /* UpdateSaveMenuState */
    CloseMenuPopup, /* CloseMenuPopup */
    OpenMenuPopup, /* OpenMenuPopup */
    UpdateQuitMenuState, /* UpdateQuitMenuState */
    ReleaseMenuPanelCallback, /* ReleaseMenuPanelCallback */
    EnterMenuFadeOutState,
    UpdateMenuFadeOutState,
    LeaveMenuFadeOutState,
    EnterMenuFadeInState,
    UpdateMenuFadeInState,
    LeaveMenuFadeInState,
};

void (*gMenuIntroUpdateCallback[1])(void) = {
    RunMenuIntroStep, /* RunMenuIntroStep */
};
