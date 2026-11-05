#include "nitro/types.h"

typedef unsigned int code();

void DrawEntrySource(int entry) {
  if ((entry != 0) && (*(code **)(entry + 0x20) != (code *)0x0)) {
    (**(code **)(entry + 0x20))(entry);
  }
}
