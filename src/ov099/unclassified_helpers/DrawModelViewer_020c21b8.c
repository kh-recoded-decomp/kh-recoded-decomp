#include "nitro/types.h"

extern void camera_commit_projection_0202a814(void *camera);
extern void AdvanceAnimationTracks_0202ef24(void *model, int step);
extern void func_ov099_020c18e8(void *model);
extern void SceneNode_Draw_01ffb12c(void *model);

void DrawModelViewer_020c21b8(u8 *viewer) {
  int index;
  u8 *model;

  camera_commit_projection_0202a814(viewer + 0x5c0);
  index = 0;
  if (**(int **)(viewer + *(int *)(viewer + 0x5bc) * 4 + 4) <= 0) {
    return;
  }
  do {
    model = viewer + 0xa8 + index * 0x104;
    AdvanceAnimationTracks_0202ef24(model, 0x1000);
    if (*(int *)(viewer + 0x5bc) == 0x21 || *(int *)(viewer + 0x5bc) == 1) {
      func_ov099_020c18e8(model);
    } else {
      SceneNode_Draw_01ffb12c(model);
    }
    index++;
  } while (index < **(int **)(viewer + *(int *)(viewer + 0x5bc) * 4 + 4));
}
