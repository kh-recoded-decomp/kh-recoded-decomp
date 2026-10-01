#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_020c3920;
extern u32 func_01ff8830();
extern u32 func_0202c8a8();
extern u32 func_0202ca18();
extern u32 func_ov001_0206a918();
extern u32 func_ov036_020bb7c0();

void func_ov036_020bd070(int ownerId) {
  int index;
  int record;

  record = data_020c3920.value;
  index = func_ov036_020bb7c0(ownerId);
  record = index * 0x9c + *(int *)(record + 0x1090);
  if (*(int *)(record + 0x74) != 0) {
    func_0202ca18(*(int *)(record + 0x74));
    func_0202c8a8(*(u32 *)(record + 0x74));
  }
  func_ov001_0206a918(record);
  func_01ff8830(record,0,0x9c);
  *(u32 *)(record + 0x8c) = 0xffffffff;
  *(u32 *)(record + 0x98) = 0xffffffff;
  *(u32 *)(record + 0x94) = 0xffffffff;
}
