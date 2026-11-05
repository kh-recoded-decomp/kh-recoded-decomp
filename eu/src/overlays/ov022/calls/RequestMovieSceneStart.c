#include "nitro/types.h"

extern u16 *data_ov022_020b7da0;
extern unsigned int QueueOrUpdateSoundKind3();

void RequestMovieSceneStart(void) {
  QueueOrUpdateSoundKind3(0x14);
  *data_ov022_020b7da0 = 1;
}
