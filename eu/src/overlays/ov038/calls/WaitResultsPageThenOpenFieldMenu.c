#include "nitro/types.h"

extern u32 OpenFieldMenuMode();
extern u32 UpdateResultsPageAndSprites();

u32 WaitResultsPageThenOpenFieldMenu(void) {
  int ready;

  ready = UpdateResultsPageAndSprites();
  if (ready != 0) {
    OpenFieldMenuMode(2);
    return 4;
  }
  return 0xffffffff;
}
