#include "nitro/types.h"

extern unsigned int func_01ff8830();
extern unsigned int func_0202ecf8();
extern unsigned int func_ov099_020c1b4c();
extern unsigned int func_ov099_020c1d00();
extern unsigned int func_ov099_020c1d5c();
extern unsigned int selectJointAnimationBlend_0202f2cc();

void func_ov099_020c2058(int work,int selection) {
  int resourceList;
  int modelIndex;
  u32 track;
  int model;

  if (0 <= *(int *)(work + 0x5bc)) {
    func_ov099_020c1d00(work);
  }
  modelIndex = 0;
  resourceList = work + selection * 4;
  if (0 < **(int **)(resourceList + 4)) {
    do {
      model = work + 0xa8 + modelIndex * 0x104;
      func_01ff8830(model,0,0x104);
      func_0202ecf8(model,(*(int *)(work + 0xa4) + 0x8000U & 0xfffffc) << 7 | 0x80000000 |
                                *(u32 *)(*(int *)(resourceList + 4) + modelIndex * 4 + 4) & 0x1ff,1,0xe);
      track = 0;
      do {
        selectJointAnimationBlend_0202f2cc(model,track & 0xffff,model + 0xd8,0);
        track = track + 1;
      } while ((int)track < 5);
      modelIndex = modelIndex + 1;
    } while (modelIndex < **(int **)(resourceList + 4));
  }
  func_ov099_020c1b4c(work,selection);
  *(int *)(work + 0x5bc) = selection;
  func_ov099_020c1d5c(work);
}
