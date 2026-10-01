#include "nitro/types.h"

extern unsigned int *data_ov021_020b56a0;
extern unsigned char data_ov021_020b5290;
extern unsigned int NNSi_FndFreeToExpHeap_0202a240();
extern unsigned int _fp_init_020bde1c();
extern unsigned int func_02029f98();
extern unsigned int func_ov043_020bccc0();
extern unsigned int func_ov044_020d067c();
extern unsigned int func_ov046_020c09fc();

void func_ov021_020af380(void) {
  switch(*data_ov021_020b56a0) {
  case 0:
    func_ov046_020c09fc();
    break;
  case 1:
    _fp_init_020bde1c();
    break;
  case 2:
    func_ov043_020bccc0();
    break;
  case 3:
    func_ov044_020d067c();
  }
  func_02029f98(0,*(int *)(&data_ov021_020b5290 + *data_ov021_020b56a0 * 4));
  *data_ov021_020b56a0 = -1;
  NNSi_FndFreeToExpHeap_0202a240
            ((void *)data_ov021_020b56a0[1],(void *)data_ov021_020b56a0[3]);
  data_ov021_020b56a0[1] = 0;
}
