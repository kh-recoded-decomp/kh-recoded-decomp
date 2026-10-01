#include "nitro/types.h"

extern int data_ov035_020bc4e0;
extern int func_0202a1c4();
extern int func_ov001_0206a918();
extern int func_ov001_0206c720();

void func_ov041_020bdc08(void) {
  int work;
  int index;
  int group;
  int groupIndex;

  work = *(int *)(data_ov035_020bc4e0 + 0xb8);
  func_ov001_0206c720(0x20bdb55);
  groupIndex = 0;
  do {
    index = 0;
    group = work + groupIndex * 8;
    if (index < (int)(u32)*(u8 *)(group + 0x318)) {
      do {
        func_ov001_0206a918(*(int *)(group + 0x314) + index * 0x34);
        index = index + 1;
      } while (index < (int)(u32)*(u8 *)(group + 0x318));
    }
    func_0202a1c4(*(int *)(group + 0x314));
    groupIndex = groupIndex + 1;
  } while (groupIndex < 4);
}
