#include "nitro/types.h"

extern u32 ScriptVm_ReadOperandInt_02025de4();
extern u32 func_ov036_020bd730();

u32 func_ov036_020be65c(void *vm,void *operands) {
  int first;
  int second;
  int third;

  first = ScriptVm_ReadOperandInt_02025de4(vm,operands);
  second = ScriptVm_ReadOperandInt_02025de4(vm,(void *)((int)operands + 8));
  third = ScriptVm_ReadOperandInt_02025de4(vm,(void *)((int)operands + 0x10));
  if (*(int *)((int)vm + 0x628) != 0) {
    return 1;
  }
  func_ov036_020bd730(first,second,third);
  return 1;
}
