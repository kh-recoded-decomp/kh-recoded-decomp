#include "nitro/types.h"

extern unsigned int *data_ov021_020b56a0;
extern unsigned int UpdateCameraBasisAndCommit_020bc854();
extern unsigned int func_ov042_020bd050();
extern unsigned int func_ov044_020d0090();
extern unsigned int func_ov046_020c0b6c();

void func_ov021_020af508(int value) {
  switch(*data_ov021_020b56a0) {
  case 0:
    func_ov046_020c0b6c();
    return;
  case 1:
    func_ov042_020bd050();
    return;
  case 2:
    UpdateCameraBasisAndCommit_020bc854(value);
    return;
  case 3:
    func_ov044_020d0090(value);
  }
}
