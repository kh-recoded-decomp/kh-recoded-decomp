#include "nitro/types.h"

extern u32 gOverlay059ActorGlobalStorage;
extern u32 GaugePanel_Update;

void UpdateGlobalActorGaugePanel(void) {
    ((void (*)(u32))&GaugePanel_Update)(gOverlay059ActorGlobalStorage + 5412);
}
