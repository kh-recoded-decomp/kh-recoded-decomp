extern unsigned int CallVirtualHandlerSlot1_02001574();
extern unsigned int DrawTextColored_02001668();
extern unsigned int Text_UploadTileBuffer_02001520();

void DrawMatrixDescriptionText_020caa30(int context)

{
  CallVirtualHandlerSlot1_02001574((void *)(context + 0x11f44),0);
  if (*(void **)(context + 0x11fac) != (void *)0x0) {
    DrawTextColored_02001668
              ((void *)(context + 0x11f44),2,4,2,10,*(void **)(context + 0x11fac));
  }
  Text_UploadTileBuffer_02001520((void *)(context + 0x11f44));
  return;
}
