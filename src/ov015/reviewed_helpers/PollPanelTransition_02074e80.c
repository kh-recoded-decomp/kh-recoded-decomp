#include "nitro/types.h"

extern u8 panelState_0207e980[];
#define transitionMode (*(int *)(panelState_0207e980 + 0x50))
extern u32 data_ov015_0207fbc0;
extern u32 func_02011ea4();
extern u32 func_ov015_020737c4();
extern u32 func_ov015_020737d4();
extern u32 func_ov015_020746f8();

void PollPanelTransition_02074e80(void)

{
  int result;
  
  if ((transitionMode == 5) && (result = func_02011ea4(&data_ov015_0207fbc0), result != 0)) {
    func_ov015_020737d4();
  }
  result = func_ov015_020746f8();
  if (result != 0) {
    return;
  }
  func_ov015_020737c4(10);
  return;
}
