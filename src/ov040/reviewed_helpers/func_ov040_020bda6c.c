#include "nitro/types.h"

extern unsigned int func_020bb014();
extern unsigned int func_020bb054();

void func_ov040_020bda6c(int entry,int offset) {
  int baseValue;

  if (entry != 0) {
    baseValue = func_020bb054();
    func_020bb014(entry,baseValue + offset);
  }
}
