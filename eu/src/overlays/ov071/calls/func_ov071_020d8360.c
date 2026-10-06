#include "nitro/types.h"

extern u32 func_ov071_020d8290();

void func_ov071_020d8360(void *actor,void *owner) {
  if (*(void **)((int)actor + 8) == owner) {
    func_ov071_020d8290(actor,owner);
  }
}
