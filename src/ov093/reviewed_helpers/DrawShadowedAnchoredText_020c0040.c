extern unsigned int DrawTextAnchored_020015a0();

void DrawShadowedAnchoredText_020c0040
               (void *renderer,int x,int y,int color,unsigned int anchor,void *text)

{
  DrawTextAnchored_020015a0(renderer,x + 1,y + 1,color + 1,anchor,text);
  DrawTextAnchored_020015a0(renderer,x,y,color,anchor,text);
  return;
}
