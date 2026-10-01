#include "nitro/types.h"

int GetAvailableMenuEntryIndex_020b763c(int menu)

{
  int index;
  
  index = -1;
  if (*(u8 *)(*(int *)(menu + 0x80) + *(int *)(menu + 0xa8)) != '\x03') {
    index = *(int *)(menu + 0xa8);
  }
  return index;
}
