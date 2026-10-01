#include "nitro/types.h"

extern unsigned int data_ov035_020bc4e0;
extern unsigned int PXI_Init_0202a638();
extern unsigned int PopVramState_020365f0();
extern unsigned int ReleaseMovieResources_020baac4();
extern unsigned int ReleaseSeqArcHeapLevel_0204e040();
extern unsigned int SuspendTaskAndSetFlag_020667b4();
extern unsigned int _fp_init_020bac70();
extern unsigned int func_0202a778();
extern unsigned int func_02036434();
extern unsigned int func_ov001_020676c4();
extern unsigned int func_ov001_020685d4();
extern unsigned int func_ov001_0207ef40();
extern unsigned int func_ov001_0207ef78();
extern unsigned int func_ov035_020bac28();
extern unsigned int func_ov035_020bac74();
extern unsigned int func_ov035_020bb788();

unsigned int func_ov035_020ba6c4(void) {
  _fp_init_020bac70();
  func_ov035_020bac74();
  func_ov035_020bac28();
  ReleaseMovieResources_020baac4();
  *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) & 0xfff3;
  func_ov001_020685d4();
  func_ov001_020676c4();
  func_ov001_0207ef40(1);
  func_ov001_0207ef78();
  func_ov035_020bb788();
  if (*(int *)(data_ov035_020bc4e0 + 0x14) != -1) {
    PXI_Init_0202a638(*(int *)(data_ov035_020bc4e0 + 0x14));
    *(unsigned int *)(data_ov035_020bc4e0 + 0x14) = 0xffffffff;
  }
  SuspendTaskAndSetFlag_020667b4();
  PopVramState_020365f0();
  func_02036434();
  ReleaseSeqArcHeapLevel_0204e040(1);
  func_0202a778(1);
  *(u16 *)(data_ov035_020bc4e0 + 6) = *(u16 *)(data_ov035_020bc4e0 + 6) | 0x8000;
  return 9;
}
