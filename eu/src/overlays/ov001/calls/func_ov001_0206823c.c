#include "nitro/types.h"

extern unsigned int *data_ov001_020a048c;

u16 func_ov001_0206823c(void) {
  return *(u16 *)
          (*(int *)(*data_ov001_020a048c + *(char *)((int)data_ov001_020a048c + 0xd) * 4 + 8) + 2)
  ;
}
