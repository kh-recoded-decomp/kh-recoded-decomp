#include "nitro/types.h"

extern u32 ScriptCmd_ShowPendingDialogText_0208c6a4();

int func_ov001_0208dc2c(void *actor) {
  int result;

  if (*(int *)((int)actor + 0x628) != 0) {
    return 1;
  }
  result = ScriptCmd_ShowPendingDialogText_0208c6a4
                    (actor,*(void **)(*(int *)((int)actor + 0x1c8) + 0x50));
  return result;
}
