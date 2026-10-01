#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int func_ov036_020be9a0();
extern unsigned int data_ov036_020c3844;
extern unsigned int data_ov036_020c392c;
extern unsigned int InitOverlayObjManager_020bf478();
extern unsigned int NNSi_FndGetCurrentRootHeap_0202a764();
extern unsigned int func_01ff8740();
extern unsigned int func_0204f58c();
extern unsigned int func_ov036_020bea80();
extern unsigned int func_ov036_020beb5c();
extern unsigned int func_ov036_020c27dc();

code * func_ov036_020be838(void) {
  int index;

  data_ov036_020c392c = NNSi_FndGetCurrentRootHeap_0202a764();
  index = 0;
  func_01ff8740(0,data_ov036_020c3844,0x68b4);
  *(unsigned int *)(data_ov036_020c3844 + 0x6458) = 1;
  *(unsigned int *)(data_ov036_020c3844 + 0x68a0) = 0xffffffff;
  *(unsigned int *)(data_ov036_020c3844 + 0x682c) = 0;
  do {
    func_ov036_020c27dc(data_ov036_020c3844 + 0x64fc + index * 0x110,0);
    index = index + 1;
  } while (index < 3);
  func_0204f58c((void *)(data_ov036_020c3844 + 0x6830),(void *)0x0);
  func_ov036_020bea80();
  func_ov036_020beb5c();
  InitOverlayObjManager_020bf478();
  return func_ov036_020be9a0;
}
