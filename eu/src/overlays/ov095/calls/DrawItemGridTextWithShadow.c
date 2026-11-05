#include "nitro/types.h"

extern u32 DrawTextColored();

void DrawItemGridTextWithShadow
               (void *layer,int x,int y,int color,int altColor,void *text) {
  DrawTextColored(layer,x + 1,y + 1,color + 1,color + 1,text);
  DrawTextColored(layer,x,y,color,altColor,text);
}
