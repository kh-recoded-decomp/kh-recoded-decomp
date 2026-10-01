#include "nitro/types.h"

extern unsigned int func_ov015_02074d44();
extern unsigned int FS_ReadFile_0201169c();
extern unsigned int func_ov015_020737c4();
extern unsigned int func_ov015_020737d4();

unsigned int func_ov015_02074d00(void) {
  void *result;

  func_ov015_020737c4(3);
  result = FS_ReadFile_0201169c(0x20803e0,func_ov015_02074d44,(void *)0x2);
  if (result != (void *)0x2) {
    func_ov015_020737d4(result);
    func_ov015_020737c4(10);
    return 0;
  }
  return 1;
}
