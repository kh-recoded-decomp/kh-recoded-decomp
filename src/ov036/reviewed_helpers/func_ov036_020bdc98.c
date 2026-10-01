#include "nitro/types.h"

extern u32 ScriptVm_ReadOperandInt_02025de4();
extern u32 func_02025438();
extern u32 func_ov036_020bca70();

u32 func_ov036_020bdc98(void *vm,void *operands) {
  int firstOrResult;
  int second;

  firstOrResult = ScriptVm_ReadOperandInt_02025de4(vm,operands);
  second = ScriptVm_ReadOperandInt_02025de4(vm,(void *)((int)operands + 8));
  firstOrResult = func_ov036_020bca70(firstOrResult,second);
  if (firstOrResult != 0) {
    func_02025438(1);
    return 1;
  }
  return 0;
}
