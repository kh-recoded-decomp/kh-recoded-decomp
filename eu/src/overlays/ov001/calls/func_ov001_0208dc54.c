#include "nitro/types.h"

extern u32 ScriptCmd_ShowPendingDialogText();

int func_ov001_0208dc54(void *actor) {
  int result;

  if (*(int *)((int)actor + 0x628) != 0) {
    return 1;
  }
  result = ScriptCmd_ShowPendingDialogText
                    (actor,*(void **)(*(int *)((int)actor + 0x1c8) + 0x50));
  return result;
}
