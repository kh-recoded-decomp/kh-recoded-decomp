#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_020c3920;
extern unsigned int func_ov036_020bb5a4();
extern unsigned int func_ov036_020bb63c();
extern unsigned int func_ov036_020bb71c();

void func_ov036_020bb544(int index) {
  int record;

  record = index * 0x9c + *(int *)(data_020c3920.value + 0x1090);
  if ((*(u16 *)(record + 0x88) & 1) != 0) {
    func_ov036_020bb5a4(record);
  }
  if ((*(u16 *)(record + 0x88) & 2) != 0) {
    func_ov036_020bb63c(record);
  }
  if ((*(u16 *)(record + 0x88) & 4) == 0) {
    return;
  }
  func_ov036_020bb71c(record);
}
