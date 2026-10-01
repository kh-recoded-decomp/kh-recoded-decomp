#include "nitro/types.h"

typedef struct { unsigned char padding[4]; int value; } SharedState;
extern SharedState data_020c0060;
extern unsigned int func_0202a778();
extern unsigned int func_02036434();
extern unsigned int func_020365f0();
extern unsigned int func_0204e040();
extern unsigned int func_ov001_02063524();
extern unsigned int func_ov001_02064d88();
extern unsigned int func_ov001_020667b4();
extern unsigned int func_ov001_020676c4();
extern unsigned int func_ov001_020685d4();
extern unsigned int func_ov001_0206c2f8();
extern unsigned int func_ov001_0206dc38();
extern unsigned int func_ov001_0206dc4c();
extern unsigned int func_ov001_0206dc80();
extern unsigned int func_ov001_0206de40();
extern unsigned int func_ov001_0207b36c();
extern unsigned int func_ov001_0207d658();
extern unsigned int func_ov001_0207ef40();
extern unsigned int func_ov001_0207ef78();

unsigned int func_ov032_020bb284(void) {
  int countOrGate;
  unsigned int firstValue;
  unsigned int secondValue;
  int index;

  if (((*(u16 *)(data_020c0060.value + 6) & 0x10) == 0) &&
     (countOrGate = func_ov001_0207b36c(), countOrGate == 0)) {
    return 0xffffffff;
  }
  func_ov001_020667b4();
  func_ov001_0206c2f8(1);
  index = 0;
  countOrGate = func_ov001_0206dc38();
  if (0 < countOrGate) {
    do {
      func_ov001_0206de40(index);
      firstValue = func_ov001_0206dc4c(index);
      secondValue = func_ov001_0206dc80(index);
      func_ov001_02063524(index,firstValue,secondValue);
      index = index + 1;
      countOrGate = func_ov001_0206dc38();
    } while (index < countOrGate);
  }
  func_ov001_020685d4();
  func_ov001_020676c4();
  func_ov001_0207ef40(1);
  func_ov001_0207ef78();
  *(u16 *)(data_020c0060.value + 6) = *(u16 *)(data_020c0060.value + 6) & 0xfff3;
  func_ov001_0207d658();
  func_ov001_02064d88();
  func_020365f0();
  func_02036434();
  func_0204e040(1);
  func_0202a778(1);
  *(u16 *)(data_020c0060.value + 6) = *(u16 *)(data_020c0060.value + 6) | 0x8000;
  return 0x11;
}
