#include "nitro/types.h"

extern unsigned int *data_ov021_020b56c0;
extern unsigned char data_ov021_020b52b0;
extern unsigned int NNSi_FndFreeToExpHeap();
extern unsigned int func_ov042_020bde3c();
extern unsigned int func_02029fac();
extern unsigned int func_ov043_020bcce0();
extern unsigned int func_ov044_020d069c();
extern unsigned int func_ov046_020c0a1c();

void func_ov021_020af3a0(void) {
  switch(*data_ov021_020b56c0) {
  case 0:
    func_ov046_020c0a1c();
    break;
  case 1:
    func_ov042_020bde3c();
    break;
  case 2:
    func_ov043_020bcce0();
    break;
  case 3:
    func_ov044_020d069c();
  }
  func_02029fac(0,*(int *)(&data_ov021_020b52b0 + *data_ov021_020b56c0 * 4));
  *data_ov021_020b56c0 = -1;
  NNSi_FndFreeToExpHeap
            ((void *)data_ov021_020b56c0[1],(void *)data_ov021_020b56c0[3]);
  data_ov021_020b56c0[1] = 0;
}
