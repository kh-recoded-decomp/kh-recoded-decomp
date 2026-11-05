#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 RuntimeState_SetObjectId();
extern u32 GetTheaterReportPhase();

void CancelTheaterEntrySelection(void) {
  int state;

  state = GetTheaterReportPhase();
  if (state != 3) {
    return;
  }
  RuntimeState_SetObjectId(0xffffffff);
  StartSubScene(0xffffffff,0xffffffff,1);
  PlaySoundEffect(0,3);
}
