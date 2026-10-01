#include "nitro/types.h"

extern unsigned int data_ov022_020b7d80;
extern unsigned int SoundMgr_Update_0204d150();
extern unsigned int func_02014008();
extern unsigned int func_ov022_020a6ec0();

void func_ov022_020a6f24(void) {
  int work;

  work = data_ov022_020b7d80;
  if (data_ov022_020b7d80 == 0) {
    return;
  }
  if (*(unsigned char *)(data_ov022_020b7d80 + 0x8b5) != '\0') {
    func_02014008();
    *(u8 *)(data_ov022_020b7d80 + 0x8b5) = 0;
  }
  func_ov022_020a6ec0(work);
  SoundMgr_Update_0204d150();
}
