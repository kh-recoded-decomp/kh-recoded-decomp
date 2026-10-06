#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_ov036_020c3940;
extern unsigned int func_ov036_020bb5c4();
extern unsigned int func_ov036_020bb65c();
extern unsigned int func_ov036_020bb73c();

void func_ov036_020bb564(int index) {
  int record;

  record = index * 0x9c + *(int *)(data_ov036_020c3940.value + 0x1090);
  if ((*(u16 *)(record + 0x88) & 1) != 0) {
    func_ov036_020bb5c4(record);
  }
  if ((*(u16 *)(record + 0x88) & 2) != 0) {
    func_ov036_020bb65c(record);
  }
  if ((*(u16 *)(record + 0x88) & 4) == 0) {
    return;
  }
  func_ov036_020bb73c(record);
}
