#include "nitro/types.h"

extern u32 gTrophyPopupWorkStorage;
extern u32 TrophyPopup_GetState();

void TrophyPopup_GetCurrentState(void) {
  TrophyPopup_GetState(gTrophyPopupWorkStorage + 44);
}
