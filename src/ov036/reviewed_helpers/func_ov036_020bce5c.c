#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_020c3920;
extern unsigned int func_ov036_020bb7c0();

void func_ov036_020bce5c(unsigned int ownerId,unsigned int target) {
  int index;
  int record;

  record = data_020c3920.value;
  index = func_ov036_020bb7c0(ownerId);
  record = index * 0x9c + *(int *)(record + 0x1090);
  if (*(u16 *)(record + 0x88) != 0) {
    return;
  }
  *(unsigned int *)(record + 0x60) = target;
  *(unsigned int *)(record + 0x58) = 0;
  *(unsigned int *)(record + 0x48) = 0x8000;
  *(unsigned int *)(record + 0x4c) = 0x8000;
  *(unsigned int *)(record + 0x50) = *(unsigned int *)(record + 0x10);
  *(unsigned int *)(record + 0x54) = *(unsigned int *)(record + 0x14);
  *(u16 *)(record + 0x88) = *(u16 *)(record + 0x88) | 2;
}
