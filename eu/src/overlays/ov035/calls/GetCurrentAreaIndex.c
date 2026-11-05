#include "nitro/types.h"

extern u32 gMovieContextState;

int GetCurrentAreaIndex(void) {
  return (int)*(char *)(gMovieContextState + 0x62);
}
