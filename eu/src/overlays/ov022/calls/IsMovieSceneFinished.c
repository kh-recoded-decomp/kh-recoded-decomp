#include "nitro/types.h"

extern u16 *gMovieSceneGlobals;

BOOL IsMovieSceneFinished(void) {
  return *gMovieSceneGlobals == 2;
}
