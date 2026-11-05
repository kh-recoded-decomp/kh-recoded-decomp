#include "nitro/types.h"

extern u32 data_ov093_020c5104;
extern u32 TrophyPopup_GetState();

void TrophyPopup_GetCurrentState(void) {
  TrophyPopup_GetState(data_ov093_020c5104 + 44);
}
