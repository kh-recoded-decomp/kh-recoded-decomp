#include "nitro/types.h"

extern u32 func_0204d924();
extern u32 func_ov039_020bbf78();
extern u32 func_ov073_020c1d38();
extern u32 func_ov076_020c544c();

void func_ov076_020c8eb0(int *work) {
  int valid;

  if ((work[10] == 0) && (*work == 1)) {
    valid = func_ov076_020c544c(work,1);
    if (valid == 0) {
      func_0204d924(1,4);
      return;
    }
    func_0204d924(1,2);
    func_ov073_020c1d38(0,0);
    func_ov039_020bbf78(3,0xffffffff,0);
  }
}
