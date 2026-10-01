#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_020bc4e8;
extern unsigned int func_ov001_020711b0();
extern unsigned int func_ov027_020b8390();
extern unsigned int func_ov027_020b83e8();

void func_ov035_020bc3b8(void) {
  int work;
  unsigned int panel;
  unsigned int record;

  work = data_020bc4e8.value;
  panel = func_ov001_020711b0();
  if (*(int *)(work + 0x18) == 100) {
    record = func_ov027_020b8390(panel,1);
    func_ov027_020b83e8(panel,record,1);
  }
}
