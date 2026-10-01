typedef void code();
extern unsigned int func_ov001_0206db5c();
extern unsigned int func_ov021_020a7fa0();

void InvokeMemberCleanupCallbacks_020ad908(int *container)

{
  int entry;
  code *callback;
  int index;
  
  if (0 < container[1]) {
    index = 0;
    if (0 < container[1]) {
      do {
        entry = *(int *)(*container + index * 4);
        if ((entry != 0) && (callback = *(code **)(entry + 0x30), callback != (code *)0x0)) {
          (*callback)(container,entry);
        }
        index = index + 1;
      } while (index < container[1]);
    }
    index = func_ov001_0206db5c(container[5]);
    func_ov021_020a7fa0(index + 0xb2c,0xffffffff);
    container[2] = 0;
  }
  return;
}
