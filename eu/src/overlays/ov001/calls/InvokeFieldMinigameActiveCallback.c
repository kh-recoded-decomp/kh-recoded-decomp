#include "nitro/types.h"

typedef unsigned int code();

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState gFieldSceneGlobals;

unsigned int InvokeFieldMinigameActiveCallback(void) {
  int result;

  if ((*(code **)(gFieldSceneGlobals.value + 0x134c) != (code *)0x0) &&
     (result = (**(code **)(gFieldSceneGlobals.value + 0x134c))(), result != 0)) {
    return 1;
  }
  return 0;
}
