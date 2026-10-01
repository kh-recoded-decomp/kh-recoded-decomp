#include "nitro/types.h"

extern unsigned int data_ov046_020c34e0;
extern unsigned int func_020c3510();
extern unsigned int func_ov046_020c0d58();
extern unsigned int func_ov046_020c0d68();

void func_ov046_020c3368(int value) {
  int work;
  int entry;

  work = func_ov046_020c0d68();
  if (work == 3) {
    entry = func_ov046_020c0d58();
    work = data_ov046_020c34e0;
    func_020c3510(entry,data_ov046_020c34e0);
    *(int *)(entry + 0x50) = value;
    if (value == 1) {
      *(unsigned int *)(work + 0x134) = 0x6000;
    }
  }
}
