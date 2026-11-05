#include "nitro/types.h"

extern u32 gMovieContextState;

int GetAreaSceneDefinitionIndex(void) {
  return (int)*(char *)(gMovieContextState + 0x1e);
}
