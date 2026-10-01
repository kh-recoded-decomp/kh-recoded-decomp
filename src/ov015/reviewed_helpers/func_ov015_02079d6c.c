#include "nitro/types.h"

extern unsigned int func_ov015_02079dcc();
extern unsigned int func_ov015_02079e5c();
extern unsigned int func_ov015_02079ed4();
extern unsigned int data_ov015_020812e0;
extern unsigned int func_ov027_020b9088();
extern unsigned int func_ov027_020b9098();

void func_ov015_02079d6c(void) {
  int work;

  work = data_ov015_020812e0;
  func_ov027_020b9098((void *)(data_ov015_020812e0 + 0x160),0x2079d08);
  func_ov027_020b9088(work + 0x160,1,func_ov015_02079dcc);
  func_ov027_020b9088(work + 0x160,0x10,func_ov015_02079e5c);
  func_ov027_020b9088(work + 0x160,0x11,func_ov015_02079ed4);
}
