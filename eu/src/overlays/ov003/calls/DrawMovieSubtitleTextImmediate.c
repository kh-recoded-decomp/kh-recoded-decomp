#include "nitro/types.h"

extern u32 IsMovieStreamReady();
extern u32 DrawNextMovieSubtitleGlyph();
extern u32 updateMovieStreamLeadTime();

void DrawMovieSubtitleTextImmediate(void *stream,u32 leadTime) {
  int ready;

  *(u32 *)((int)stream + 0x68) = leadTime;
  updateMovieStreamLeadTime((int)stream);
  ready = IsMovieStreamReady(stream);
  while (ready != 0) {
    DrawNextMovieSubtitleGlyph(stream);
    ready = IsMovieStreamReady(stream);
  }
  *(u32 *)((int)stream + 0x68) = 0;
  *(u32 *)((int)stream + 0x58) = 0;
  *(u32 *)((int)stream + 0x60) = 0;
  *(u32 *)((int)stream + 0x44) = 1;
}
