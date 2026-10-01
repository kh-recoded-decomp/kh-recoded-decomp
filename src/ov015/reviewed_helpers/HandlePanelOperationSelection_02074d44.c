#include "nitro/types.h"

extern u8 panelState_0207e980[];
#define operationHandle (*(u32 *)(panelState_0207e980 + 0x48))
extern u32 func_0201141c();
extern u32 func_ov015_020737c4();
extern u32 func_ov015_020737d4();

void HandlePanelOperationSelection_02074d44(int context)

{
  int result;
  
  if (*(u16 *)(context + 2) != 0) {
    func_ov015_020737d4();
    func_ov015_020737c4(10);
    return;
  }
  result = func_0201141c(operationHandle);
  if (result != 0) {
    func_ov015_020737d4();
    func_ov015_020737c4(10);
    return;
  }
  func_ov015_020737c4(1);
  return;
}
