#include "nitro/types.h"

extern u32 resultsState_020c0f80[2];
#define resultsWork ((int)resultsState_020c0f80[1])
typedef struct SystemFlags { u8 pad[6]; u16 mode : 3; u16 rest : 13; } SystemFlags;
extern SystemFlags globalState_0206085c;
#define systemFlags globalState_0206085c.mode
extern u32 func_02025438();
extern u32 func_0202a778();
extern u32 func_0204e040();
extern u32 func_ov034_020bcdf0();

u32 FinishResultsScreen_020bdc3c(void)

{
  func_ov034_020bcdf0();
  func_02025438(1);
  if ((*(int *)(resultsWork + 0x6d90) != 1) || (systemFlags != 1)) {
    func_0204e040(1);
  }
  func_0202a778(1);
  *(u16 *)(resultsWork + 6) = *(u16 *)(resultsWork + 6) | 0x8000;
  return 3;
}
