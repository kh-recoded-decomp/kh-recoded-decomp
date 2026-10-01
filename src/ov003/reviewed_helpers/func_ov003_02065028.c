#include "nitro/types.h"

extern u32 IsMovieStreamReady_02064fd8();
extern u32 func_ov022_02064ec4();
extern u32 updateMovieStreamLeadTime_02064e2c();

void func_ov003_02065028(void *stream,u32 leadTime) {
  int ready;

  *(u32 *)((int)stream + 0x68) = leadTime;
  updateMovieStreamLeadTime_02064e2c((int)stream);
  ready = IsMovieStreamReady_02064fd8(stream);
  while (ready != 0) {
    func_ov022_02064ec4(stream);
    ready = IsMovieStreamReady_02064fd8(stream);
  }
  *(u32 *)((int)stream + 0x68) = 0;
  *(u32 *)((int)stream + 0x58) = 0;
  *(u32 *)((int)stream + 0x60) = 0;
  *(u32 *)((int)stream + 0x44) = 1;
}
