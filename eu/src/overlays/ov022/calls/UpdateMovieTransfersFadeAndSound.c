#include "nitro/types.h"

extern unsigned int gMovieSceneGlobals;
extern unsigned int SoundMgr_Update();
extern unsigned int NNS_GfdDoVramTransfer();
extern unsigned int UpdateMovieFadeOut();

void UpdateMovieTransfersFadeAndSound(void) {
  int work;

  work = gMovieSceneGlobals;
  if (gMovieSceneGlobals == 0) {
    return;
  }
  if (*(unsigned char *)(gMovieSceneGlobals + 0x8b5) != '\0') {
    NNS_GfdDoVramTransfer();
    *(u8 *)(gMovieSceneGlobals + 0x8b5) = 0;
  }
  UpdateMovieFadeOut(work);
  SoundMgr_Update();
}
