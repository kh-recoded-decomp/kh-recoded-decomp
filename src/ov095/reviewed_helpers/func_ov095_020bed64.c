#include "nitro/types.h"

extern u32 data_ov095_020c2888;
extern u32 func_02001154();
extern u32 func_0202cd78();
extern u32 func_02050a44();
extern u32 func_02051cdc();
extern u32 func_02051dfc();
extern u32 func_ov039_020bc688();
extern u32 func_ov095_020bf7f4();
extern u32 func_ov095_020bf9a8();
extern u32 func_ov095_020c01ac();
extern u32 func_ov095_020c0704();
extern u32 func_ov095_020c098c();

void func_ov095_020bed64(int work) {
  int containerIndex;

  containerIndex = 0;
  func_02001154(1,&data_ov095_020c2888,0);
  func_ov095_020c098c(work);
  func_ov095_020c0704(work);
  func_ov095_020c01ac(work);
  func_ov095_020bf9a8(work);
  func_ov095_020bf7f4(work);
  func_02050a44();
  func_02051dfc(1);
  func_02051dfc(5);
  func_02051dfc(0);
  func_02051cdc();
  do {
    func_0202cd78(*(u32 *)(work + containerIndex * 4 + 8));
    containerIndex = containerIndex + 1;
  } while (containerIndex < 3);
  func_ov039_020bc688(0,5);
}
