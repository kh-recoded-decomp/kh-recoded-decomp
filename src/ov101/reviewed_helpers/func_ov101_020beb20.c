#include "nitro/types.h"

extern unsigned int func_ov101_020c0d9c();
extern unsigned int data_ov101_020c4d20;
extern unsigned int data_ov101_020c0ee0;
extern unsigned int data_ov101_020c0f0c;
extern unsigned int data_ov101_020c1378;
extern unsigned int IsStateFlagSet_020c07a8();
extern unsigned int SetEntryAnimFrame_020bfcd0();
extern unsigned int SetGlobalPackedBit_02027320();
extern unsigned int SetStateFlagBits_020bc688();
extern unsigned int SetStatePhase_020c0c18();
extern unsigned int func_01ff8740();
extern unsigned int func_0200110c();
extern unsigned int func_ov039_020bc828();
extern unsigned int func_ov101_020bf004();
extern unsigned int func_ov101_020bf24c();
extern unsigned int func_ov101_020bf2b8();
extern unsigned int func_ov101_020bf400();
extern unsigned int func_ov101_020bf634();
extern unsigned int func_ov101_020bf8a4();
extern unsigned int func_ov101_020bfd90();
extern unsigned int func_ov101_020c0578();
extern unsigned int func_ov101_020c07d4();
extern unsigned int func_ov101_020c07f4();

unsigned int func_ov101_020beb20(int *work) {
  int indexOrState;
  int entryOrState;

  data_ov101_020c4d20 = work;
  SetStateFlagBits_020bc688('\x05','\0');
  func_01ff8740(0,work,0xcfd8);
  indexOrState = func_ov039_020bc828();
  *work = indexOrState;
  work[0x33f1] = 0;
  work[0x33f2] = 0;
  work[0x3397] = 0;
  work[0x33f3] = 0;
  work[0x33f5] = 0;
  work[0x33f4] = 0;
  func_ov101_020c07f4(work);
  func_01ff8740(0,work + 0x3398,0xa0);
  func_ov101_020bf004(work);
  func_ov101_020bf24c(work);
  func_ov101_020bf2b8(work);
  func_ov101_020bf400(work);
  func_ov101_020bf8a4(work);
  func_ov101_020c0578(work);
  func_ov101_020bfd90(&data_ov101_020c0ee0,work);
  func_ov101_020bfd90(&data_ov101_020c0f0c,work);
  func_ov101_020bf634(0xffffffff,work);
  func_0200110c(1,&data_ov101_020c1378,func_ov101_020c0d9c,0);
  entryOrState = *work;
  indexOrState = IsStateFlagSet_020c07a8(1,entryOrState);
  if (indexOrState != 0) {
    func_ov101_020c07d4(2,entryOrState);
    SetGlobalPackedBit_02027320(entryOrState + 0x1272);
  }
  indexOrState = 0;
  do {
    entryOrState = IsStateFlagSet_020c07a8(2,indexOrState);
    SetEntryAnimFrame_020bfcd0(0,indexOrState + 3,(u32)(entryOrState != 0),work);
    indexOrState = indexOrState + 1;
  } while (indexOrState < 9);
  SetStatePhase_020c0c18(0);
  return 1;
}
