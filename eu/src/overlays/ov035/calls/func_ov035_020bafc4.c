#include "nitro/types.h"

extern u32 gMovieContextState;

int func_ov035_020bafc4(void) {
  return (int)*(char *)(gMovieContextState + 0x1e);
}
