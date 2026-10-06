#include "nitro/types.h"

extern unsigned int MI_CpuFill8();
extern unsigned int InitSharedRecordAndDispatch();
extern unsigned int func_ov099_020c1b6c();
extern unsigned int ReleaseViewerModels();
extern unsigned int func_ov099_020c1d7c();
extern unsigned int selectJointAnimationBlend();

void func_ov099_020c2078(int work,int selection) {
  int resourceList;
  int modelIndex;
  u32 track;
  int model;

  if (0 <= *(int *)(work + 0x5bc)) {
    ReleaseViewerModels(work);
  }
  modelIndex = 0;
  resourceList = work + selection * 4;
  if (0 < **(int **)(resourceList + 4)) {
    do {
      model = work + 0xa8 + modelIndex * 0x104;
      MI_CpuFill8(model,0,0x104);
      InitSharedRecordAndDispatch(model,(*(int *)(work + 0xa4) + 0x8000U & 0xfffffc) << 7 | 0x80000000 |
                                *(u32 *)(*(int *)(resourceList + 4) + modelIndex * 4 + 4) & 0x1ff,1,0xe);
      track = 0;
      do {
        selectJointAnimationBlend(model,track & 0xffff,model + 0xd8,0);
        track = track + 1;
      } while ((int)track < 5);
      modelIndex = modelIndex + 1;
    } while (modelIndex < **(int **)(resourceList + 4));
  }
  func_ov099_020c1b6c(work,selection);
  *(int *)(work + 0x5bc) = selection;
  func_ov099_020c1d7c(work);
}
