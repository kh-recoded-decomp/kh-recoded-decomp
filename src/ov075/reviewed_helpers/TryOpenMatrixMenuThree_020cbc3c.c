#include "nitro/types.h"

extern u32 func_0204d924();
extern u32 func_ov039_020bbf78();
extern u32 func_ov039_020bca00();
extern u32 func_ov075_020c42b4();

void TryOpenMatrixMenuThree_020cbc3c(int context)

{
  int result;
  
  if ((((((*(int *)(context + 0x78) != 0) && (*(int *)(context + 0x12dc8) == 0)) &&
        (*(int *)(context + 0x74) == 0)) &&
       ((*(int *)(context + 0x17524) == 0 && (*(int *)(context + 0x88) == 0)))) &&
      ((*(int *)(context + 0x13ea0) == 0 &&
       ((*(u16 *)(context + 0x13e64) == 0 && (result = func_ov075_020c42b4(context), result == 0)))))) &&
     (result = func_ov039_020bca00(), (*(u16 *)(result + 8) & 3) == 0)) {
    func_0204d924(1,2);
    func_ov039_020bbf78(3,0xffffffff,0);
  }
  return;
}
