#include "nitro/types.h"

typedef unsigned int code();

extern unsigned char data_ov091_020c281c;
extern unsigned int func_ov091_020bf540();
extern unsigned int func_ov091_020bf8ac();
extern unsigned int func_ov091_020c1754();

void func_ov091_020bed64(unsigned int work) {
  int state;

  state = func_ov091_020c1754();
  if (*(code **)(&data_ov091_020c281c + state * 4) != (code *)0x0) {
    (**(code **)(&data_ov091_020c281c + state * 4))(work);
  }
  func_ov091_020bf540(work);
  func_ov091_020bf8ac(work);
}
