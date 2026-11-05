extern void FreePointerIfSet(void *state);
extern void DestroyFndObjectList(void *context);
void DestroyOverlay088CaptionLayer(void *context) {
    FreePointerIfSet((char *)context + 0x34);
    DestroyFndObjectList(context);
}
