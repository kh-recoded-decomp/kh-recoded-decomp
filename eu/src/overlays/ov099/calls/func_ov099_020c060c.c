#include "nitro/types.h"

extern u32 DrawTextColored();

void func_ov099_020c060c
               (void *layer,int x,int y,int color,int flags,void *text) {
  DrawTextColored(layer,x + 1,y + 1,color + 1,color + 1,text);
  DrawTextColored(layer,x,y,color,flags,text);
}
