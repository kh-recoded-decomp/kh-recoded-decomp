#include "nitro/types.h"

extern unsigned int *data_ov001_020a0470;
extern unsigned int func_ov001_020644b0();
extern unsigned int func_ov001_0206844c();
extern unsigned int func_ov001_02068530();
extern unsigned int func_ov032_020bb86c();

void func_ov001_02068a74(int index,unsigned int secondValue,unsigned int firstValue) {
  int resolvedKind;
  int records;
  u32 kind;

  records = *(int *)(*data_ov001_020a0470 + 4);
  kind = (u32)*(u8 *)(records + index * 0xc);
  resolvedKind = func_ov001_020644b0();
  if (resolvedKind == 900) {
    kind = func_ov032_020bb86c(*(u8 *)(records + index * 0xc));
  }
  resolvedKind = func_ov001_02068530(kind);
  if (resolvedKind != 0x28) {
    func_ov001_0206844c(firstValue,resolvedKind,secondValue,1);
  }
}
