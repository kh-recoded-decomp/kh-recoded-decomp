#include "nitro/types.h"

extern unsigned int data_ov039_020bea00;
extern unsigned int func_ov039_020baae0();
extern unsigned int func_ov039_020bc018();
extern unsigned int func_ov039_020bcf20();
extern unsigned int func_ov039_020bd054();

void func_ov039_020bb2b0(void) {
  int work;

  work = data_ov039_020bea00;
  func_ov039_020bcf20(*(unsigned int *)(data_ov039_020bea00 + 0xc998));
  func_ov039_020bd054(*(unsigned int *)(work + 0xc99c));
  if (((u32)*(int *)(work + 0xc9e8) << 29) >> 31 == 0) {
    return;
  }
  *(unsigned int *)(work + 0xca0c) = 0;
  func_ov039_020bc018(1);
  func_ov039_020baae0(3);
}
