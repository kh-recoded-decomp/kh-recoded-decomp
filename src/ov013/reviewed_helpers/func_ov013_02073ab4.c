#include "nitro/types.h"

extern unsigned int data_ov013_02074ce0;
extern unsigned int func_0204d924();
extern unsigned int func_ov002_0206671c();
extern unsigned int func_ov002_02066b2c();
extern unsigned int func_ov013_0206f06c();
extern unsigned int func_ov013_0206fbbc();
extern unsigned int func_ov013_020704a0();
extern unsigned int func_ov013_02070ce8();
extern unsigned int func_ov013_020716e4();

void func_ov013_02073ab4(void) {
  int active;
  u8 inputState [8];

  func_ov002_0206671c();
  if (*(int *)(data_ov013_02074ce0 + 700) == 0) {
    *(int *)(data_ov013_02074ce0 + 0x2cc) =
         *(int *)(data_ov013_02074ce0 + 0x2cc) - *(int *)(data_ov013_02074ce0 + 0x300);
    if (*(int *)(data_ov013_02074ce0 + 0x2cc) < *(int *)(data_ov013_02074ce0 + 0x2e0)) {
      *(int *)(data_ov013_02074ce0 + 0x2cc) = *(int *)(data_ov013_02074ce0 + 0x2e0);
      func_ov013_020716e4(1);
      return;
    }
    func_ov013_020704a0();
    func_ov013_0206fbbc();
    func_ov013_0206f06c();
    if (*(unsigned char *)(data_ov013_02074ce0 + 600 + (int)*(char *)(data_ov013_02074ce0 + 0x2f0)) ==
        '\x01') {
      *(u8 *)(data_ov013_02074ce0 + 600 + (int)*(char *)(data_ov013_02074ce0 + 0x2f0)) = 2
      ;
      func_ov013_02070ce8();
    }
    func_0204d924(2,0);
    *(unsigned int *)(data_ov013_02074ce0 + 700) = 2;
  }
  else {
    *(int *)(data_ov013_02074ce0 + 700) = *(int *)(data_ov013_02074ce0 + 700) + -1;
  }
  active = func_ov002_02066b2c(inputState);
  if (active == 0) {
    func_ov013_020716e4(1);
    return;
  }
}
