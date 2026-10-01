#include "nitro/types.h"

extern unsigned int data_ov073_020c4188;
extern unsigned int G2D_GetScreenFromFile_02014dd0();
extern unsigned int func_01ff869c();
extern unsigned int func_0200110c();
extern unsigned int func_02014d38();
extern unsigned int func_0202a1c4();
extern unsigned int func_0202b554();
extern unsigned int func_0202c48c();
extern unsigned int func_ov027_020b9df0();
extern unsigned int func_ov039_020bc128();
extern unsigned int func_ov039_020bc1e4();
extern unsigned int func_ov039_020bc220();
extern unsigned int func_ov039_020bc6b0();

void func_ov073_020c173c(unsigned int event,int work) {
  unsigned int file;
  unsigned int destination;
  unsigned int size;
  int firstScreen;
  int secondScreen;

  if (*(int *)(work + 0x188) == 0) {
    file = func_0202c48c((*(int *)(work + 0x140) + 0x8000U & 0xfffffc) << 7 | 0x8000000b,
                                0xe);
    *(unsigned int *)(work + 0x188) = file;
    func_0202b554(work + 0x18c,*(unsigned int *)(work + 0x188),0xffffffff,0xffffffff,0);
  }
  if (*(int *)(work + 0x184) == 0) {
    file = func_ov039_020bc220(0,9);
    file = func_0202c48c(file,0xe);
    *(unsigned int *)(work + 0x184) = file;
    func_02014d38(file,work + 0x180);
  }
  file = func_ov039_020bc220(0,10);
  file = func_0202c48c(file,0xe);
  G2D_GetScreenFromFile_02014dd0(file,&firstScreen);
  size = *(unsigned int *)(firstScreen + 8);
  destination = func_ov027_020b9df0(work + 0x148,0x1b);
  func_01ff869c(firstScreen + 0xc,destination,size);
  func_0202a1c4(file);
  file = func_ov039_020bc220(0,0xb);
  file = func_0202c48c(file,0xe);
  G2D_GetScreenFromFile_02014dd0(file,&secondScreen);
  size = *(unsigned int *)(secondScreen + 8);
  destination = func_ov039_020bc1e4(0x19);
  func_01ff869c(secondScreen + 0xc,destination,size);
  func_0202a1c4(file);
  func_ov039_020bc128(0x18);
  func_ov039_020bc128(0x19);
  func_ov039_020bc128(0x1a);
  func_ov039_020bc128(0x1b);
  func_ov039_020bc6b0(0x20c1249);
  *(unsigned int *)(work + 0x204) = 2;
  if (*(int *)(work + 0x164) == 0) {
    func_0200110c(1,&data_ov073_020c4188,0x20c1369,0);
    *(unsigned int *)(work + 0x164) = 1;
  }
}
