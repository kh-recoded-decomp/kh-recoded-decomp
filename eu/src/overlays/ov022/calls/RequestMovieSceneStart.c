#include "nitro/types.h"

extern u16 *gMovieSceneGlobals;
extern unsigned int QueueOrUpdateSoundKind3();

void RequestMovieSceneStart(void) {
  QueueOrUpdateSoundKind3(0x14);
  *gMovieSceneGlobals = 1;
}
