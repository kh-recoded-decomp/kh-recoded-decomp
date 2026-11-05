#include "nitro/types.h"

extern u32 DeactivateOv071TaskEntriesAndManager();

void func_ov071_020d8360(void *actor,void *owner) {
  if (*(void **)((int)actor + 8) == owner) {
    DeactivateOv071TaskEntriesAndManager(actor,owner);
  }
}
