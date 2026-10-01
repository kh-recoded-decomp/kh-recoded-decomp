#include "nitro/types.h"

#define false 0
#define true 1
extern u8 data_ov075_020d1454[];

u8 * GetMatrixModeLabel_020c575c(int mode)

{
  if ((mode < 3) || (mode >= 14)) {
    mode = 0;
  }
  else {
    mode = mode + -2;
  }
  return data_ov075_020d1454 + mode * 4;
}
