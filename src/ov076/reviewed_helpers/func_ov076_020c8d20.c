#include "nitro/types.h"

extern u32 func_02027304();
extern u32 func_0204d924();
extern u32 func_ov039_020bbf78();
extern u32 func_ov039_020bc8d0();
extern u32 func_ov076_020c544c();

void func_ov076_020c8d20(int *work) {
  int result;

  if ((work[10] == 0) && (*work == 1)) {
    result = func_ov076_020c544c(work,1);
    if (result == 0) {
      func_0204d924(1,4);
      return;
    }
    func_0204d924(1,3);
    result = func_02027304(0xf5b);
    func_ov039_020bc8d0(result != 0);
    func_ov039_020bbf78(0,0xffffffff,1);
  }
}
