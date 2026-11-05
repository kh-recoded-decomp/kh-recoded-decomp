#include "nitro/types.h"

extern unsigned int gMovieContextState;

BOOL IsAreaSceneStartupComplete(void) {
  if (gMovieContextState == 0) {
    return FALSE;
  }
  return (*(u16 *)(gMovieContextState + 6) & 1) == 0;
}
