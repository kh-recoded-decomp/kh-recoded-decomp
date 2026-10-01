#include "nitro/types.h"

typedef unsigned int code();

extern unsigned int GetBoundedEntryField_0206db5c();

int func_ov001_0206dc60(int index) {
  u32 entry;
  int result;

  entry = GetBoundedEntryField_0206db5c(index);
  if (entry == 0) {
    return 0;
  }
  if (*(code **)(entry + 0x224) != (code *)0x0) {
    result = (**(code **)(entry + 0x224))();
    return result;
  }
  return entry + 0xbc;
}
