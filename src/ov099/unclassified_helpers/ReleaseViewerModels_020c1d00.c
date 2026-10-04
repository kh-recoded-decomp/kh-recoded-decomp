#include "nitro/types.h"

extern void ReleaseResourceAndDetach_0202eee8(void *model);
extern void NNS_GfdResetFrmTexVramState_0201391c(void);
extern void func_02013d74(void);

void ReleaseViewerModels_020c1d00(u8 *viewer) {
  int index = 0;

  if (**(int **)(viewer + *(int *)(viewer + 0x5bc) * 4 + 4) > 0) {
    do {
      ReleaseResourceAndDetach_0202eee8(viewer + 0xa8 + index * 0x104);
      index++;
    } while (index < **(int **)(viewer + *(int *)(viewer + 0x5bc) * 4 + 4));
  }
  NNS_GfdResetFrmTexVramState_0201391c();
  func_02013d74();
}
