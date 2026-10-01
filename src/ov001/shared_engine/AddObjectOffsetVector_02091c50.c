#include "nitro/types.h"

extern u32 VEC_Add_01ff9e0c();

void AddObjectOffsetVector_02091c50(int object,void *offset)

{
  if ((object != 0) && (offset != (void *)0x0)) {
    VEC_Add_01ff9e0c((void *)(object + 0x374),offset,(void *)(object + 0x374));
  }
  return;
}
