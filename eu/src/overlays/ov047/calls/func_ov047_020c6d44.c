#include "nitro/types.h"

extern u32 Camera_Update();
extern u32 Camera_RestoreSavedTracking();

void func_ov047_020c6d44(void) {
  Camera_RestoreSavedTracking();
  Camera_Update(1);
}
