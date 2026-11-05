#include "nitro/types.h"

extern u32 Camera_Update();
extern u32 Camera_RestoreSavedTracking();

void RestoreCameraTrackingAndUpdate(void) {
  Camera_RestoreSavedTracking();
  Camera_Update(1);
}
