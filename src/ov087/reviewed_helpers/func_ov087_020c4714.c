#include "nitro/types.h"

extern u32 DrawTextAnchored_020015a0();
extern u32 Text_UploadTileBuffer_02001520();

void func_ov087_020c4714(int work,int windowIndex,void *text,int color) {
  DrawTextAnchored_020015a0
            ((void *)(work + 0x9f8 + windowIndex * 0x34),0x40,2,color,0x411,text);
  Text_UploadTileBuffer_02001520((void *)(work + 0x9f8 + windowIndex * 0x34));
}
