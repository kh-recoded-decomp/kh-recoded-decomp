#include "nitro/types.h"

extern unsigned int *gActiveSubModeState;
extern unsigned int UpdateCameraBasisAndCommit();
extern unsigned int CommitCameraFrame();
extern unsigned int CommitPanelCameraFrame();
extern unsigned int Camera_Update();

void UpdateActiveSubModeCamera(int value) {
  switch(*gActiveSubModeState) {
  case 0:
    Camera_Update();
    return;
  case 1:
    CommitCameraFrame();
    return;
  case 2:
    UpdateCameraBasisAndCommit(value);
    return;
  case 3:
    CommitPanelCameraFrame(value);
  }
}
