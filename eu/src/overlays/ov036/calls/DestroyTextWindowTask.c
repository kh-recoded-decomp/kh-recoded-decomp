#include "nitro/types.h"

extern u32 gTextWindowResourceTable;
extern u32 FSi_DefaultStepDoneB();
extern u32 ReleaseTextWindowBackground();
extern u32 ReleaseTextWindowFonts();
extern u32 ReleaseTextWindowDisplayList();

void DestroyTextWindowTask(void) {
  ReleaseTextWindowDisplayList();
  ReleaseTextWindowFonts();
  ReleaseTextWindowBackground();
  FSi_DefaultStepDoneB(gTextWindowResourceTable + 0x6830);
  gTextWindowResourceTable = 0;
}
