#include "nitro/types.h"

extern u32 DrawTextColored_02001668();

void func_ov095_020c0044
               (void *layer,int x,int y,int color,int flags,void *text) {
  DrawTextColored_02001668(layer,x + 1,y + 1,color + 1,color + 1,text);
  DrawTextColored_02001668(layer,x,y,color,flags,text);
}
