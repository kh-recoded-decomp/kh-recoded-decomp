#include "nitro/types.h"

extern u32 data_ov042_020be5e0;
extern u32 QuadTree_InsertObject();
extern u32 QuadTree_RemoveObject();
extern u32 GetActorRegistry();

void func_ov042_020bd11c(u32 newMode) {
  int work;
  int actorManager;

  work = data_ov042_020be5e0;
  *(u32 *)(data_ov042_020be5e0 + 0x44) = *(u32 *)(data_ov042_020be5e0 + 0x40);
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
