typedef void code();
extern unsigned int func_0202a1c4();

void ReleaseCallbackOwnedBuffer_020aafac(int object)

{
  if (*(code **)(object + 0x24) != (code *)0x0) {
    (**(code **)(object + 0x24))(object);
    if (*(int *)(object + 0xc) != 0) {
      func_0202a1c4(*(int *)(object + 0xc));
    }
  }
  return;
}
