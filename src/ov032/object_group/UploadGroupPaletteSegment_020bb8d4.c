#include "nitro/types.h"

extern u32 data_ov032_020c0044;
extern u32 data_ov032_020c004e;
extern u32 GFXi_EnqueueCommand_02014090();

void UploadGroupPaletteSegment_020bb8d4(int alternate)

{
  u8 *palette;
  
  palette = &data_ov032_020c004e;
  if (alternate == 0) {
    palette = &data_ov032_020c0044;
  }
  GFXi_EnqueueCommand_02014090((void *)0xf,0x184,(int)palette,10);
  return;
}
