extern unsigned int CopyClippedScreenRegion_020167d0();
extern unsigned int func_ov027_020b9970();

void CopyWidgetScreenRegion_020b9b18(int screen,int widget,void *destination)

{
  int width;
  int height;
  
  if (destination != (void *)0x0) {
    func_ov027_020b9970(widget,&width,&height);
    CopyClippedScreenRegion_020167d0
              (destination,*(void **)(*(int *)(widget + 0x18) + 8),(unsigned int)*(unsigned short *)(widget + 6),
               (unsigned int)*(unsigned short *)(widget + 8),(int)*(short *)(widget + 2),
               (int)*(short *)(widget + 4),(unsigned int)*(unsigned short *)(screen + 8),
               (unsigned int)*(unsigned short *)(screen + 10),width,height);
    return;
  }
  return;
}
