#include "nitro/types.h"

extern u32 Text_UploadTileBuffer_02001520();

void UploadDirtySubtitleTiles_020a914c(void *stream)

{
  if (*(int *)((int)stream + 0x44) == 0) {
    return;
  }
  Text_UploadTileBuffer_02001520(stream);
  *(u32 *)((int)stream + 0x44) = 0;
  return;
}
