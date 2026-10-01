#include "nitro/types.h"

extern u32 IsMovieStreamReady_020a90a8();
extern u32 func_ov022_020a8f94();
extern u32 updateMovieStreamLeadTime_020a8efc();

void func_ov022_020a90f8(void *stream,u32 leadTime) {
  int ready;

  *(u32 *)((int)stream + 0x68) = leadTime;
  updateMovieStreamLeadTime_020a8efc((int)stream);
  ready = IsMovieStreamReady_020a90a8(stream);
  while (ready != 0) {
    func_ov022_020a8f94(stream);
    ready = IsMovieStreamReady_020a90a8(stream);
  }
  *(u32 *)((int)stream + 0x68) = 0;
  *(u32 *)((int)stream + 0x58) = 0;
  *(u32 *)((int)stream + 0x60) = 0;
  *(u32 *)((int)stream + 0x44) = 1;
}
