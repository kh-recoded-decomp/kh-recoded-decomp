#include "nitro/types.h"

extern unsigned int data_ov022_020b7da0;
extern unsigned int SoundMgr_Update();
extern unsigned int NNS_GfdDoVramTransfer();
extern unsigned int UpdateMovieFadeOut();

void func_ov022_020a6f44(void) {
  int work;

  work = data_ov022_020b7da0;
  if (data_ov022_020b7da0 == 0) {
    return;
  }
  if (*(unsigned char *)(data_ov022_020b7da0 + 0x8b5) != '\0') {
    NNS_GfdDoVramTransfer();
    *(u8 *)(data_ov022_020b7da0 + 0x8b5) = 0;
  }
  UpdateMovieFadeOut(work);
  SoundMgr_Update();
}
