#include "nitro/types.h"

extern u32 gCameraSceneGlobalStorage;
extern u32 QuadTree_InsertObject();
extern u32 QuadTree_RemoveObject();
extern u32 GetActorRegistry();

void SetCameraColliderRegistrationMode(u32 newMode) {
  int work;
  int actorManager;

  work = gCameraSceneGlobalStorage;
  *(u32 *)(gCameraSceneGlobalStorage + 0x44) = *(u32 *)(gCameraSceneGlobalStorage + 0x40);
  *(u32 *)(work + 0x40) = newMode;
  actorManager = GetActorRegistry();
  QuadTree_RemoveObject(**(u32 **)(actorManager + 4),work + 0x40c);
  QuadTree_RemoveObject(**(u32 **)(actorManager + 4),work + 0x494);
  QuadTree_RemoveObject(**(u32 **)(actorManager + 4),work + 0x51c);
  if (*(int *)(work + 0x40) == 1) {
    QuadTree_InsertObject(**(u32 **)(actorManager + 4),work + 0x40c);
    QuadTree_InsertObject(**(u32 **)(actorManager + 4),work + 0x494);
    QuadTree_InsertObject(**(u32 **)(actorManager + 4),work + 0x51c);
  }
}
