#include "nitro/types.h"

typedef struct { unsigned char padding[0xd4]; unsigned int value; } SharedState;
extern SharedState data_0205a924;
extern unsigned int data_ov099_020c28e0;
extern unsigned int data_0205a9b8;
extern unsigned int func_01ff87c4();
extern unsigned int func_01ff90ec();
extern unsigned int func_02019188();
extern unsigned int func_0202cd78();
extern unsigned int func_02051cdc();
extern unsigned int func_02051dfc();
extern unsigned int func_ov039_020bc688();
extern unsigned int func_ov099_020bf434();
extern unsigned int func_ov099_020bf5a4();
extern unsigned int func_ov099_020bf79c();
extern unsigned int func_ov099_020c07c8();
extern unsigned int func_ov099_020c2198();

void func_ov099_020bedb0(int work) {
  u8 identityMatrix [36];

  func_ov099_020c2198(work + 0xd0ec);
  func_ov099_020c07c8(work);
  func_ov099_020bf79c(work);
  func_ov099_020bf5a4(work);
  func_ov099_020bf434(work);
  func_01ff90ec(identityMatrix);
  func_01ff87c4(identityMatrix,&data_0205a9b8);
  data_0205a924.value = data_0205a924.value & 0xffffff5b;
  func_02019188();
  func_02051dfc(4);
  func_02051dfc(0);
  func_02051cdc();
  func_0202cd78(*(unsigned int *)(work + 0x30c));
  func_ov039_020bc688(0,5);
  data_ov099_020c28e0 = 0;
}
