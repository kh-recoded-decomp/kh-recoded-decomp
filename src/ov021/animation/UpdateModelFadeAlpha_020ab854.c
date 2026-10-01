#include "nitro/types.h"

extern u32 FixedPointMultiply12();
extern u32 Model_SetAllMaterialAlpha_0201a900();
extern u32 func_ov021_020ab83c();

void UpdateModelFadeAlpha_020ab854(int object,int delta)

{
  int alpha;
  
  if ((*(char *)(object + 0x131) != '\0') && (*(char *)(object + 0x131) == '\x01')) {
    alpha = FixedPointMultiply12(delta,0x1b00);
    alpha = *(int *)(object + 0x144) - alpha;
    *(int *)(object + 0x144) = alpha;
    if (alpha <= 0) {
      func_ov021_020ab83c(object);
    }
    Model_SetAllMaterialAlpha_0201a900
              (*(void **)(object + 0x78),*(int *)(object + 0x144) >> 0xc);
  }
  return;
}
