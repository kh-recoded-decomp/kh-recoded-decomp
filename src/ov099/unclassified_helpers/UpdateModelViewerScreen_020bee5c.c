#include "nitro/types.h"

typedef void (*ModeHandler)(u8 *work);

extern const ModeHandler data_ov099_020c224c[];
extern int func_ov099_020c1778(u8 *work);
extern void ResetObjManagerLists_020c07fc(u8 *work);
extern void DrawModelViewer_020c21b8(u8 *viewer);

void UpdateModelViewerScreen_020bee5c(u8 *work) {
  int mode = func_ov099_020c1778(work);

  if (data_ov099_020c224c[mode] != NULL) {
    data_ov099_020c224c[mode](work);
  }
  if (++*(int *)(work + 0xd6e4) >= 0x3c) {
    *(int *)(work + 0xd6e4) = 0;
    *(int *)(work + 0xd6e8) = (*(int *)(work + 0xd6e8) + 1) % 2;
  }
  ResetObjManagerLists_020c07fc(work);
  DrawModelViewer_020c21b8(work + 0xd0ec);
}
