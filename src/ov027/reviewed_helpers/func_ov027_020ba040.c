#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int func_ov027_020ba104();
extern unsigned int data_ov027_020ba3c4;
extern unsigned int NNSi_FndGetCurrentRootHeap_0202a764();
extern unsigned int func_01ff8830();
extern unsigned int func_0201288c();

code * func_ov027_020ba040(void) {
  void *work;

  work = NNSi_FndGetCurrentRootHeap_0202a764();
  data_ov027_020ba3c4 = work;
  func_01ff8830(work,0,0x18);
  func_0201288c(work,0x18);
  func_0201288c((int)work + 0xc,0x18);
  return func_ov027_020ba104;
}
