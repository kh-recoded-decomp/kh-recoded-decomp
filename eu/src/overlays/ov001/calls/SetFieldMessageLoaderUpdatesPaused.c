#include "nitro/types.h"

extern u32 *gFieldMessageSpriteManager;

void SetFieldMessageLoaderUpdatesPaused(int enabled) {
  if (gFieldMessageSpriteManager != (u32 *)0x0) {
    if (enabled != 0) {
      *gFieldMessageSpriteManager = *gFieldMessageSpriteManager | 1;
      return;
    }
    *gFieldMessageSpriteManager = *gFieldMessageSpriteManager & 0xfffffffe;
  }
}
