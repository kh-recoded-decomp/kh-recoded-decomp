#include "nitro/types.h"

extern unsigned int *data_ov010_020a1dc0;
extern unsigned int data_ov010_020a1da0;
extern unsigned int data_ov010_020a1db0;
extern unsigned int Msg_OpenContainerAndReadHeader_0202cc6c();
extern unsigned int NNSi_FndAllocFromDefaultHeap_0202a178();
extern unsigned int func_ov001_020645e8();
extern unsigned int func_ov010_020a0d24();
extern unsigned int func_ov046_020c2ec0();

void func_ov010_020a17a0(unsigned int value) {
  unsigned int *work;
  void *resource;

  if (data_ov010_020a1dc0 == (unsigned int *)0x0) {
    data_ov010_020a1dc0 = NNSi_FndAllocFromDefaultHeap_0202a178(0x9c);
    resource = Msg_OpenContainerAndReadHeader_0202cc6c(&data_ov010_020a1da0,8,0);
    data_ov010_020a1dc0[0xb] = resource;
    func_ov010_020a0d24(data_ov010_020a1dc0);
  }
  work = data_ov010_020a1dc0;
  *data_ov010_020a1dc0 = 0;
  work[8] = value;
  work[2] = 0;
  work[3] = 0;
  work[6] = 0xffffffff;
  work[10] = 0;
  work[9] = 0;
  func_ov001_020645e8(0x3716);
  func_ov001_020645e8(0x3717);
  func_ov046_020c2ec0(work + 0xf,&data_ov010_020a1db0);
}
