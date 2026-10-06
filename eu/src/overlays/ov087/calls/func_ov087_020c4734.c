#include "nitro/types.h"

extern u32 DrawTextAnchored();
extern u32 Text_UploadTileBuffer();

void func_ov087_020c4734(int work,int windowIndex,void *text,int color) {
  DrawTextAnchored
            ((void *)(work + 0x9f8 + windowIndex * 0x34),0x40,2,color,0x411,text);
  Text_UploadTileBuffer((void *)(work + 0x9f8 + windowIndex * 0x34));
}
