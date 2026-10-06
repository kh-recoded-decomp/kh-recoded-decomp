#include "nitro/types.h"

extern unsigned int *data_ov021_020b56c0;
extern unsigned int UpdateCameraBasisAndCommit();
extern unsigned int func_ov042_020bd070();
extern unsigned int func_ov044_020d00b0();
extern unsigned int Camera_Update();

void func_ov021_020af528(int value) {
  switch(*data_ov021_020b56c0) {
  case 0:
    Camera_Update();
    return;
  case 1:
    func_ov042_020bd070();
    return;
  case 2:
    UpdateCameraBasisAndCommit(value);
    return;
  case 3:
    func_ov044_020d00b0(value);
  }
}
