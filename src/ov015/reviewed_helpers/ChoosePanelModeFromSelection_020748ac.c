#include "nitro/types.h"

extern u32 func_ov015_020737c4();

void ChoosePanelModeFromSelection_020748ac(int context)

{
  if (*(u16 *)(context + 2) != 0) {
    func_ov015_020737c4(10);
    return;
  }
  func_ov015_020737c4(0);
  return;
}
