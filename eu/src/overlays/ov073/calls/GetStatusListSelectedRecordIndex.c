#include "nitro/types.h"

u32 GetStatusListSelectedRecordIndex(int work) {
  if (*(u8 *)(*(int *)(work + 0x80) + *(int *)(work + 0xa8)) == '\x03') {
    return 0xffffffff;
  }
  return (u32)*(u16 *)(*(int *)(*(int *)(work + 4) + 4) + *(int *)(work + 0xa8) * 8 + 8);
}
