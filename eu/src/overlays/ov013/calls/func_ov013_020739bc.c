#include "nitro/types.h"

extern unsigned int data_ov013_02074ce0;
extern unsigned int PlaySoundEffect();
extern unsigned int UpdateMenuTouch();
extern unsigned int GetMenuTouchHeld();
extern unsigned int RefreshProgressCaption();
extern unsigned int func_ov013_0206fbbc();
extern unsigned int func_ov013_020704a0();
extern unsigned int RefreshPanelSlotMarkers();
extern unsigned int func_ov013_020716e4();

void func_ov013_020739bc(void) {
  int active;
  u8 inputState [8];

  UpdateMenuTouch();
  if (*(int *)(data_ov013_02074ce0 + 700) == 0) {
    *(int *)(data_ov013_02074ce0 + 0x2cc) =
         *(int *)(data_ov013_02074ce0 + 0x2cc) + *(int *)(data_ov013_02074ce0 + 0x300);
    if (0 < *(int *)(data_ov013_02074ce0 + 0x2cc)) {
      *(unsigned int *)(data_ov013_02074ce0 + 0x2cc) = 0;
      func_ov013_020716e4(1);
      return;
    }
    func_ov013_020704a0();
    func_ov013_0206fbbc();
    RefreshProgressCaption();
    if (*(unsigned char *)(data_ov013_02074ce0 + 600 + (int)*(char *)(data_ov013_02074ce0 + 0x2f0)) ==
        '\x01') {
      *(u8 *)(data_ov013_02074ce0 + 600 + (int)*(char *)(data_ov013_02074ce0 + 0x2f0)) = 2
      ;
      RefreshPanelSlotMarkers();
    }
    PlaySoundEffect(2,0);
    *(unsigned int *)(data_ov013_02074ce0 + 700) = 2;
  }
  else {
    *(int *)(data_ov013_02074ce0 + 700) = *(int *)(data_ov013_02074ce0 + 700) + -1;
  }
  active = GetMenuTouchHeld(inputState);
  if (active == 0) {
    func_ov013_020716e4(1);
    return;
  }
}
