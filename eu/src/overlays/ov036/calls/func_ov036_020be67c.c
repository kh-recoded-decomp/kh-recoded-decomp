#include "nitro/types.h"

extern u32 ScriptVm_ReadOperandInt();
extern u32 func_ov036_020bd750();

u32 func_ov036_020be67c(void *vm,void *operands) {
  int first;
  int second;
  int third;

  first = ScriptVm_ReadOperandInt(vm,operands);
  second = ScriptVm_ReadOperandInt(vm,(void *)((int)operands + 8));
  third = ScriptVm_ReadOperandInt(vm,(void *)((int)operands + 0x10));
  if (*(int *)((int)vm + 0x628) != 0) {
    return 1;
  }
  func_ov036_020bd750(first,second,third);
  return 1;
}
