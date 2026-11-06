#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState gEvent2DPanelManager;
extern unsigned int MI_CpuFill8();

void ClearPanelWindowWaitState(void) {
  MI_CpuFill8(gEvent2DPanelManager.value + 0x10ec,0,0x10);
}
