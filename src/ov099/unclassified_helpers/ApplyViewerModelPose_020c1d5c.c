#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ViewerModel {
  u16 flags;
  u8 pad02[0x7a];
  u16 rotation;
  u8 pad7e[0x26];
  VecFx32 position;
  VecFx32 scale;
  u8 padBc[0x48];
} ViewerModel;

typedef struct ModelViewer {
  int *table;
  int *modeCounts[0x28];
  u32 header;
  ViewerModel models[5];
  int mode;
} ModelViewer;

extern fx32 data_ov099_020c27cc[];
extern void MI_CpuCopy8_01ff89a8(const void *source, void *destination, u32 size);

static inline void GetModelPosition(ViewerModel *model, VecFx32 *out) {
  MI_CpuCopy8_01ff89a8(&model->position, out, sizeof(VecFx32));
}

void ApplyViewerModelPose_020c1d5c(ModelViewer *viewer) {
  int i;
  VecFx32 slidePos;
  VecFx32 upPos;
  VecFx32 downPos;
  VecFx32 offsetPos;

  for (i = 0; i < *viewer->modeCounts[viewer->mode]; i++) {
    viewer->models[i].scale.x = viewer->models[i].scale.y = viewer->models[i].scale.z =
        data_ov099_020c27cc[viewer->mode];
  }
  if (viewer->mode == 0xc) {
    for (i = 0; i < *viewer->modeCounts[viewer->mode]; i++) {
      viewer->models[i].rotation = 0x4000;
      viewer->models[i].flags |= 0x20;
    }
  }
  if (viewer->mode == 0x1b || viewer->mode == 0x1f || viewer->mode == 0x26) {
    for (i = 0; i < *viewer->modeCounts[viewer->mode]; i++) {
      viewer->models[i].rotation = 0x1555;
      viewer->models[i].flags |= 0x20;
      GetModelPosition(&viewer->models[i], &slidePos);
      if (viewer->mode == 0x1b) {
        slidePos.x -= 0xcd;
      } else {
        slidePos.x -= 0x266;
      }
      viewer->models[i].position = slidePos;
    }
  }
  if (viewer->mode == 6) {
    for (i = 0; i < *viewer->modeCounts[viewer->mode]; i++) {
      viewer->models[i].rotation = 0xc000;
      viewer->models[i].flags |= 0x20;
      GetModelPosition(&viewer->models[i], &upPos);
      upPos.x += 0x400;
      viewer->models[i].position = upPos;
    }
  }
  if (viewer->mode == 0x20) {
    for (i = 0; i < *viewer->modeCounts[viewer->mode]; i++) {
      viewer->models[i].rotation = 0xc000;
      viewer->models[i].flags |= 0x20;
      GetModelPosition(&viewer->models[i], &downPos);
      downPos.x -= 0x400;
      viewer->models[i].position = downPos;
    }
  }
  if (viewer->mode == 0x19) {
    for (i = 0; i < *viewer->modeCounts[viewer->mode]; i++) {
      GetModelPosition(&viewer->models[i], &offsetPos);
      offsetPos.y += 0x119a;
      viewer->models[i].position = offsetPos;
    }
  }
}
