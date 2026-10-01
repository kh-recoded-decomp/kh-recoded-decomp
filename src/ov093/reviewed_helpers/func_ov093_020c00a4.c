#include "nitro/types.h"

extern u32 DrawTextColored_02001668();

void func_ov093_020c00a4
               (void *layer,int x,int y,int color,u32 flags,void *text) {
  DrawTextColored_02001668(layer,x + 1,y + 1,color + 1,color + 1,text);
  DrawTextColored_02001668(layer,x,y,color,7,text);
}
