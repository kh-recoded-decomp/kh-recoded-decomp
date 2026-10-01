#include "nitro/types.h"

extern u32 data_ov042_020be5c0;
extern u32 func_02033c3c();
extern u32 func_02033c60();
extern u32 func_02036230();

void func_ov042_020bd0fc(u32 newMode) {
  int work;
  int actorManager;

  work = data_ov042_020be5c0;
  *(u32 *)(data_ov042_020be5c0 + 0x44) = *(u32 *)(data_ov042_020be5c0 + 0x40);
  *(u32 *)(work + 0x40) = newMode;
  actorManager = func_02036230();
  func_02033c60(**(u32 **)(actorManager + 4),work + 0x40c);
  func_02033c60(**(u32 **)(actorManager + 4),work + 0x494);
  func_02033c60(**(u32 **)(actorManager + 4),work + 0x51c);
  if (*(int *)(work + 0x40) == 1) {
    func_02033c3c(**(u32 **)(actorManager + 4),work + 0x40c);
    func_02033c3c(**(u32 **)(actorManager + 4),work + 0x494);
    func_02033c3c(**(u32 **)(actorManager + 4),work + 0x51c);
  }
}
