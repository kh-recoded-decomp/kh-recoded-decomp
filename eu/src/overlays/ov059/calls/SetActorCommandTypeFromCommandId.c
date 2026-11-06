#include "nitro/types.h"

extern u32 gOverlay059ActorGlobalStorage;
extern u32 Actor_SetCommandType();

void SetActorCommandTypeFromCommandId(u32 command) {
  switch(command) {
  case 0x1f8:
    Actor_SetCommandType(gOverlay059ActorGlobalStorage,0);
    return;
  case 0x1f9:
    Actor_SetCommandType(gOverlay059ActorGlobalStorage,1);
    return;
  case 0x1fa:
    Actor_SetCommandType(gOverlay059ActorGlobalStorage,2);
    return;
  case 0x1fb:
    Actor_SetCommandType(gOverlay059ActorGlobalStorage,3);
  }
}
