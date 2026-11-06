#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState gEvent2DPanelManager;

void Event2DSceneOnLeaveClearFlag2(void) {
  *(u16 *)(gEvent2DPanelManager.value + 6) = *(u16 *)(gEvent2DPanelManager.value + 6) & 0xfffd;
}
