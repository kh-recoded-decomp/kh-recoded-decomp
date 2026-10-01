#include "nitro/types.h"

extern u32 *data_ov023_020b6f64;
extern u8 data_ov023_020b6edc;
extern u32 func_0204f24c();
extern u32 func_0204f378();
extern u32 func_ov001_0207b4d8();
extern u32 func_ov001_0207b4e8();
extern u32 func_ov001_0207b6f4();
extern u32 func_ov027_020ba114();

void func_ov023_020b6c48(u32 index,u32 value) {
  u32 *work;
  u32 mode;
  int resourceIndex;
  u32 *base;

  work = data_ov023_020b6f64;
  *data_ov023_020b6f64 = index;
  work[1] = value;
  base = work + 0x16;
  func_0204f24c(base,work[0x1923],work[8] != 1);
  func_0204f378(base,work[0x1924],1);
  resourceIndex = 0;
  do {
    mode = 4;
    if (work[8] != 1) {
      mode = 5;
    }
    func_0204f24c(base,work[resourceIndex + 0x1925],mode);
    resourceIndex = resourceIndex + 1;
  } while (resourceIndex < 2);
  work[0xd] = 0;
  if (index >= 8) {
    func_ov001_0207b4d8();
    func_ov001_0207b6f4();
    return;
  }
  func_ov001_0207b4e8();
  func_ov027_020ba114
            ((work[2] + 0x8000 & 0xfffffc) << 7 | 0x80000000 |
             *(u16 *)(&data_ov023_020b6edc + index * 2) & 0x1ff,1,0x20b5bcd,0);
}
