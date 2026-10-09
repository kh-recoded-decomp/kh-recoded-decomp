#include "nitro/types.h"

extern unsigned int gMovieContextState;
extern unsigned int GetMovieEntryKind();

int func_ov035_020bb2c0(void) {
  int state;
  int index;
  int count;

  count = 0;
  index = 0;
  if (index < (int)(u32)*(u8 *)(gMovieContextState + 0x42)) {
    do {
      state = GetMovieEntryKind(index);
      if (state == 0) {
        count = count + 1;
      }
      index = index + 1;
    } while (index < (int)(u32)*(u8 *)(gMovieContextState + 0x42));
  }
  return count;
}
