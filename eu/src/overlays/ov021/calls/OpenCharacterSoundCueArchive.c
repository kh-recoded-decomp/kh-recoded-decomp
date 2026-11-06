#include "nitro/types.h"

extern u32 gCharacterSoundCueArchive;
extern u32 sOv021_BaChSeP2_020b5200;
extern u32 Msg_OpenContainerAndReadHeader();

void OpenCharacterSoundCueArchive(void) {
  gCharacterSoundCueArchive = Msg_OpenContainerAndReadHeader(&sOv021_BaChSeP2_020b5200,0x11,0);
}
