#include "nitro/types.h"

typedef struct { unsigned char padding[0xd4]; unsigned int value; } SharedState;
extern SharedState NNS_G3dGlb;
extern unsigned int data_ov099_020c2900;
extern unsigned int NNS_G3dGlb_prmBaseRot;
extern unsigned int MI_Copy36B();
extern unsigned int MTX_Identity33_();
extern unsigned int NNS_G3dGlbFlushP();
extern unsigned int ZeroHalfThenFree();
extern unsigned int ReleaseRecordManager();
extern unsigned int ReleaseRecordSlot();
extern unsigned int SetStateFlagBits();
extern unsigned int FreeLoadedFiles_020bf454();
extern unsigned int FreeResourceBlocks_020bf5c4();
extern unsigned int FreeViewerResources();
extern unsigned int ReleaseObjManagers();
extern unsigned int DestroyModelViewer();

void func_ov099_020bedd0(int work) {
  u8 identityMatrix [36];

  DestroyModelViewer(work + 0xd0ec);
  ReleaseObjManagers(work);
  FreeViewerResources(work);
  FreeResourceBlocks_020bf5c4(work);
  FreeLoadedFiles_020bf454(work);
  MTX_Identity33_(identityMatrix);
  MI_Copy36B(identityMatrix,&NNS_G3dGlb_prmBaseRot);
  NNS_G3dGlb.value = NNS_G3dGlb.value & 0xffffff5b;
  NNS_G3dGlbFlushP();
  ReleaseRecordSlot(4);
  ReleaseRecordSlot(0);
  ReleaseRecordManager();
  ZeroHalfThenFree(*(unsigned int *)(work + 0x30c));
  SetStateFlagBits(0,5);
  data_ov099_020c2900 = 0;
}
