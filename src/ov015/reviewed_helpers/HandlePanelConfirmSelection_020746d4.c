#include "nitro/types.h"

extern u32 func_ov015_020737c4();
extern u32 func_ov015_020737d4();

void HandlePanelConfirmSelection_020746d4(int context)

{
  if (*(u16 *)(context + 2) != 0) {
    func_ov015_020737d4();
    return;
  }
  func_ov015_020737c4(1);
  return;
}
