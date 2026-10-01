#include "nitro/types.h"

extern u32 data_ov040_020be264;
extern u32 func_0202a178();
extern u32 func_ov001_0206dba0();
extern u32 func_ov021_020adaf0();
extern u32 func_ov021_020adb44();

void func_ov040_020bdf7c(int actor,u32 owner) {
  u32 *handles;
  int archive;
  u32 handle;
  u32 fileBase;

  handles = (u32 *)func_0202a178(0x14);
  data_ov040_020be264 = handles;
  archive = func_ov001_0206dba0(4);
  fileBase = (archive + 0x8000U & 0xfffffc) * 0x80;
  handle = func_ov021_020adaf0(actor + 0x1070,owner,0,fileBase | 0x80000000);
  *handles = handle;
  handle = func_ov021_020adaf0(actor + 0x1070,owner,0xe,fileBase | 0x8000000e);
  handles[1] = handle;
  handle = func_ov021_020adb44(actor + 0x1070,owner,0,0);
  handles[2] = handle;
  handles[3] = 0;
}
