#include "nitro/types.h"

extern unsigned int *data_ov010_020a1de0;
extern unsigned int sOv010_BaEfFnW7P2_020a1dc0;
extern unsigned int sOv010_CmDD_020a1dd0;
extern unsigned int Msg_OpenContainerAndReadHeader();
extern unsigned int NNSi_FndAllocFromDefaultHeap();
extern unsigned int ClearSessionPackedBit();
extern unsigned int LoadObjectSprites();
extern unsigned int CameraPath_Load();

void func_ov010_020a17c0(unsigned int value) {
  unsigned int *work;
  void *resource;

  if (data_ov010_020a1de0 == (unsigned int *)0x0) {
    data_ov010_020a1de0 = NNSi_FndAllocFromDefaultHeap(0x9c);
    resource = Msg_OpenContainerAndReadHeader(&sOv010_BaEfFnW7P2_020a1dc0,8,0);
    data_ov010_020a1de0[0xb] = resource;
    LoadObjectSprites(data_ov010_020a1de0);
  }
  work = data_ov010_020a1de0;
  *data_ov010_020a1de0 = 0;
  work[8] = value;
  work[2] = 0;
  work[3] = 0;
  work[6] = 0xffffffff;
  work[10] = 0;
  work[9] = 0;
  ClearSessionPackedBit(0x3716);
  ClearSessionPackedBit(0x3717);
  CameraPath_Load(work + 0xf,&sOv010_CmDD_020a1dd0);
}
