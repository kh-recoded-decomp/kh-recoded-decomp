extern unsigned int func_0202f4e8();
extern unsigned int func_0202f4d8();

void SetObjectAnimationEnabled_020a9d28(unsigned int *object,int enabled)

{
  if ((*object & 1) != 0) {
    if (enabled != 0) {
      func_0202f4d8(object + 2);
      if (object[0x8a] != 0) {
        func_0202f4d8(object[0x8a]);
      }
    }
    else {
      func_0202f4e8(object + 2);
      if (object[0x8a] != 0) {
        func_0202f4e8(object[0x8a]);
        return;
      }
    }
  }
  return;
}
