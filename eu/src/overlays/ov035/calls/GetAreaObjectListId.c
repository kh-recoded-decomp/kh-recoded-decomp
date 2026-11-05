#include "nitro/types.h"

extern u32 gMovieContextState;

int GetAreaObjectListId(void) {
  return (int)*(char *)(gMovieContextState + 0x43);
}
