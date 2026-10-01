#include "nitro/types.h"

extern unsigned int data_ov001_020a0460;
extern unsigned int data_ov033_020baac0;
extern unsigned int func_02025438();
extern unsigned int func_0202a778();
extern unsigned int func_0204d9a8();
extern unsigned int func_0204e040();
extern unsigned int func_ov001_02063130();
extern unsigned int func_ov001_020642b4();
extern unsigned int func_ov039_020bbe60();

unsigned int func_ov033_020ba72c(void) {
  unsigned int mode;

  func_ov039_020bbe60(0);
  func_0204d9a8(0x7f,10);
  mode = 1;
  func_02025438(1);
  if ((*(u32 *)(data_ov001_020a0460 + 0x214) << 0x12 >> 0x1f) == 0) {
    if (*(int *)(data_ov033_020baac0 + 0xc) != 0) {
      if (*(int *)(data_ov033_020baac0 + 8) == 6) {
        mode = 3;
      }
      func_ov001_02063130((int)*(short *)(data_ov033_020baac0 + 4),mode);
    }
    func_ov001_020642b4();
  }
  func_0204e040(1);
  func_0202a778(1);
  *(u16 *)(data_ov033_020baac0 + 6) = *(u16 *)(data_ov033_020baac0 + 6) | 0x8000;
  return 3;
}
