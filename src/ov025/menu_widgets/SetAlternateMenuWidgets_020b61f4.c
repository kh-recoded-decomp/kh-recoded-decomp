#include "nitro/types.h"

extern u32 _data_ov025_020b7760;
extern u32 func_ov027_020b90a4();
extern u32 func_ov027_020b9580();

void SetAlternateMenuWidgets_020b61f4(int enabled)

{
  int menu;
  u32 widget;
  
  menu = _data_ov025_020b7760;
  *(u8 *)(_data_ov025_020b7760 + 0x64e9) = enabled != 0;
  if (enabled != 0) {
    widget = func_ov027_020b90a4(menu + 0x4c,0x15);
    func_ov027_020b9580(menu + 0x4c,widget,1);
    widget = func_ov027_020b90a4(menu + 0x4c,3);
    func_ov027_020b9580(menu + 0x4c,widget,0);
    return;
  }
  widget = func_ov027_020b90a4(menu + 0x4c,0x15);
  func_ov027_020b9580(menu + 0x4c,widget,0);
  widget = func_ov027_020b90a4(menu + 0x4c,3);
  func_ov027_020b9580(menu + 0x4c,widget,1);
  return;
}
