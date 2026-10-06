#include "nitro/types.h"

extern unsigned int *data_ov001_020a048c;
extern unsigned int HighlightSelectedMenuPanels();

u8 func_ov001_02067ee4(int index,u8 value,int refresh) {
  u8 previous;
  u8 *entry;

  entry = *(u8 **)(*data_ov001_020a048c + index * 4 + 8);
  previous = *entry;
  *entry = value;
  if (refresh != 0) {
    HighlightSelectedMenuPanels();
  }
  return previous;
}
