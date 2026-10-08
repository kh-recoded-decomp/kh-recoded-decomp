#include "nitro/types.h"

typedef unsigned int code();

extern unsigned char gResultsPageStateHandlers;
extern unsigned int InitOv038SlotPools();
extern unsigned int GetResultsPageState();

unsigned int func_ov038_020bbd08(void) {
  int state;
  unsigned int result;

  state = GetResultsPageState();
  result = (**(code **)(&gResultsPageStateHandlers + state * 4))();
  InitOv038SlotPools();
  return result;
}
