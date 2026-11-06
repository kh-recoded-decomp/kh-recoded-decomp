#include "nitro/types.h"

extern unsigned int gOv013PanelGlobals;
extern unsigned int PlaySoundEffect();
extern unsigned int UpdateMenuTouch();
extern unsigned int GetMenuTouchHeld();
extern unsigned int RefreshProgressCaption();
extern unsigned int PositionOv013CursorWidget();
extern void ScrollPanelSlotWidgets(void);
extern unsigned int RefreshPanelSlotMarkers();
extern unsigned int ChangePanelMenuState();

void UpdateOv013HeldScrollTowardStart(void) {
  int active;
  u8 inputState [8];

  UpdateMenuTouch();
  if (*(int *)(gOv013PanelGlobals + 700) == 0) {
    *(int *)(gOv013PanelGlobals + 0x2cc) =
         *(int *)(gOv013PanelGlobals + 0x2cc) + *(int *)(gOv013PanelGlobals + 0x300);
    if (0 < *(int *)(gOv013PanelGlobals + 0x2cc)) {
      *(unsigned int *)(gOv013PanelGlobals + 0x2cc) = 0;
      ChangePanelMenuState(1);
      return;
    }
    ScrollPanelSlotWidgets();
    PositionOv013CursorWidget();
    RefreshProgressCaption();
    if (*(unsigned char *)(gOv013PanelGlobals + 600 + (int)*(char *)(gOv013PanelGlobals + 0x2f0)) ==
        '\x01') {
      *(u8 *)(gOv013PanelGlobals + 600 + (int)*(char *)(gOv013PanelGlobals + 0x2f0)) = 2
      ;
      RefreshPanelSlotMarkers();
    }
    PlaySoundEffect(2,0);
    *(unsigned int *)(gOv013PanelGlobals + 700) = 2;
  }
  else {
    *(int *)(gOv013PanelGlobals + 700) = *(int *)(gOv013PanelGlobals + 700) + -1;
  }
  active = GetMenuTouchHeld(inputState);
  if (active == 0) {
    ChangePanelMenuState(1);
    return;
  }
}
