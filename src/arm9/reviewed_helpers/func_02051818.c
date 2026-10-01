#include "nitro/types.h"

extern unsigned int *data_020613d0;
extern unsigned int func_0202c478();
extern unsigned int func_0202c48c();

void func_02051818(int alternateLoader,unsigned int unused,u32 loaderValue,u32 loaderExtra) {
  int *work;
  u32 resource;

  work = data_020613d0;
  if (alternateLoader != 0) {
    resource = func_0202c48c((*data_020613d0 + 0x8000U & 0xfffffc) << 7 | 0x80000006,0x11,loaderValue,
                          loaderExtra);
    work[0xf] = resource;
    return;
  }
  resource = func_0202c478((*data_020613d0 + 0x8000U & 0xfffffc) << 7 | 0x80000006,0x11,loaderValue,
                        loaderExtra);
  work[0xf] = resource;
}
