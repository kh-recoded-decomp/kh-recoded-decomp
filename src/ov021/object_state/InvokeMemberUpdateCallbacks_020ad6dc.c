typedef void code();
extern unsigned int func_ov021_020aca30();

void InvokeMemberUpdateCallbacks_020ad6dc(int *container,unsigned int argument)

{
  int entry;
  int index;
  
  if (0 < container[1]) {
    func_ov021_020aca30(container);
    index = 0;
    if (0 < container[1]) {
      do {
        entry = *(int *)(*container + index * 4);
        if ((entry != 0) && (*(code **)(entry + 0x24) != (code *)0x0)) {
          (**(code **)(entry + 0x24))(container,entry,argument);
        }
        index = index + 1;
      } while (index < container[1]);
    }
  }
  return;
}
