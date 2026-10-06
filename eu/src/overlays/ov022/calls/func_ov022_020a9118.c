#include "nitro/types.h"

extern u32 IsMovieStreamReady_020a90c8();
extern u32 DrawNextSubtitleGlyph();
extern u32 updateMovieStreamLeadTime_020a8f1c();

void func_ov022_020a9118(void *stream,u32 leadTime) {
  int ready;

  *(u32 *)((int)stream + 0x68) = leadTime;
  updateMovieStreamLeadTime_020a8f1c((int)stream);
  ready = IsMovieStreamReady_020a90c8(stream);
  while (ready != 0) {
    DrawNextSubtitleGlyph(stream);
    ready = IsMovieStreamReady_020a90c8(stream);
  }
  *(u32 *)((int)stream + 0x68) = 0;
  *(u32 *)((int)stream + 0x58) = 0;
  *(u32 *)((int)stream + 0x60) = 0;
  *(u32 *)((int)stream + 0x44) = 1;
}
