#include "nitro/types.h"

typedef unsigned int code();

extern unsigned char gResultsPageStateHandlers;
extern unsigned int UpdateResultsPageSpriteManagers();
extern unsigned int GetResultsPageState();

unsigned int UpdateResultsPageAndSprites(void) {
  int state;
  unsigned int result;

  state = GetResultsPageState();
  result = (**(code **)(&gResultsPageStateHandlers + state * 4))();
  UpdateResultsPageSpriteManagers();
  return result;
}
