#include "nitro/types.h"

typedef unsigned int code();

void UpdateEntrySource(int entry,unsigned int value) {
  if ((entry != 0) && (*(code **)(entry + 0x1c) != (code *)0x0)) {
    (**(code **)(entry + 0x1c))(entry,value);
  }
}
