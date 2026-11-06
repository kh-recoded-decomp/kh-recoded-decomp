/* Preserve the original wrapper's CodeWarrior integer types. */
#include "../include/nitro/types.h"

#include "nitro/types.h"

/* The task runner consumes native 32-bit callback words; zero retains its current state. */
extern void *(*ScreenFadeInStep(void))(void);
extern void *(*ScreenFadeOutStep(void))(void);
extern void *(*StepBrightnessFadeIn(void))(void);
extern void *StepBrightnessFade(void);

extern unsigned int *gFieldScreenTransitionWork;

unsigned int SelectScreenFadeHandler(void) {
  unsigned int callback;
  u32 flags;

  callback = 0;
  flags = *gFieldScreenTransitionWork;
  if ((flags & 0x20) == 0) {
    if ((flags & 1) != 0) {
      return (unsigned int)ScreenFadeInStep;
    }
    if ((flags & 2) != 0) {
      return (unsigned int)ScreenFadeOutStep;
    }
    if ((flags & 4) != 0) {
      return (unsigned int)StepBrightnessFadeIn;
    }
    if ((flags & 8) != 0) {
      callback = (unsigned int)StepBrightnessFade;
    }
  }
  return callback;
}
