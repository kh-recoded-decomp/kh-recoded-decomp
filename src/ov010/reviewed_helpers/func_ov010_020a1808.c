#include "nitro/types.h"

extern unsigned int data_ov010_020a1dc0;
extern unsigned int func_0202a1c4();
extern unsigned int func_0202cd78();
extern unsigned int func_020c2f90();
extern unsigned int func_ov010_020a0d00();

void func_ov010_020a1808(void) {
  if (data_ov010_020a1dc0 != 0) {
    func_ov010_020a0d00();
    func_0202cd78(*(unsigned int *)(data_ov010_020a1dc0 + 0x2c));
    func_020c2f90(data_ov010_020a1dc0 + 0x3c);
    func_0202a1c4(data_ov010_020a1dc0);
  }
  data_ov010_020a1dc0 = 0;
}
