#include "nitro/types.h"

extern u32 HasMovieSubtitleCodeUnit();
extern u32 DrawNextSubtitleGlyph();
extern u32 UpdateMovieSubtitleLineAlignment();

void DrawMovieSubtitleText(void *stream,u32 leadTime) {
  int ready;

  *(u32 *)((int)stream + 0x68) = leadTime;
  UpdateMovieSubtitleLineAlignment((int)stream);
  ready = HasMovieSubtitleCodeUnit(stream);
  while (ready != 0) {
    DrawNextSubtitleGlyph(stream);
    ready = HasMovieSubtitleCodeUnit(stream);
  }
  *(u32 *)((int)stream + 0x68) = 0;
  *(u32 *)((int)stream + 0x58) = 0;
  *(u32 *)((int)stream + 0x60) = 0;
  *(u32 *)((int)stream + 0x44) = 1;
}
