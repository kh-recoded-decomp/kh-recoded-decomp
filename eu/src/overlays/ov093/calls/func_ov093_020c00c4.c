#include "nitro/types.h"

extern u32 DrawTextColored();

void func_ov093_020c00c4
               (void *layer,int x,int y,int color,u32 flags,void *text) {
  DrawTextColored(layer,x + 1,y + 1,color + 1,color + 1,text);
  DrawTextColored(layer,x,y,color,7,text);
}
