#include "nitro/types.h"

extern u32 DrawTextColored();

void func_ov095_020c0064
               (void *layer,int x,int y,int color,int flags,void *text) {
  DrawTextColored(layer,x + 1,y + 1,color + 1,color + 1,text);
  DrawTextColored(layer,x,y,color,flags,text);
}
