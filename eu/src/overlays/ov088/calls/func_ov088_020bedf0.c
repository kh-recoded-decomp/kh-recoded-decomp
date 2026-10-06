extern void FreePointerIfSet(void *state);
extern void DestroyFndObjectList(void *context);
void func_ov088_020bedf0(void *context) {
    FreePointerIfSet((char *)context + 0x34);
    DestroyFndObjectList(context);
}
