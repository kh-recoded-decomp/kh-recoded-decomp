#include "nitro/types.h"

extern unsigned int func_01ffa0f4();
extern unsigned int func_020be0c4();
extern unsigned int func_ov001_0206ca68();
extern unsigned int func_ov001_0206db5c();
extern unsigned int func_ov001_0206dc38();
extern unsigned int func_ov001_0206dc4c();
extern unsigned int func_ov007_020a0ff8();

void func_ov007_020a0908(int work) {
  int result;
  unsigned int value;
  unsigned int position;

  result = func_ov001_0206dc38();
  if (result <= 0) {
    return;
  }
  value = func_ov007_020a0ff8(work);
  position = func_ov001_0206dc4c(0);
  result = func_01ffa0f4(value,position);
  if (*(int *)(*(int *)(work + 8) + 0x4c) < result) {
    return;
  }
  value = func_ov001_0206db5c(0);
  result = func_020be0c4(value,(int)*(short *)(work + 0xac),*(u8 *)(work + 0xae));
  if (result != 0) {
    func_ov001_0206ca68(0,2,0);
    return;
  }
  func_ov001_0206ca68(0,1,0);
}
