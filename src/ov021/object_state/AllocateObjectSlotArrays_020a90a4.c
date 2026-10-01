extern unsigned int func_0202a178();

void AllocateObjectSlotArrays_020a90a4(int *container,int count)

{
  int index;
  
  container[1] = count;
  index = func_0202a178(count * 0x2c);
  *container = index;
  index = func_0202a178(count);
  container[2] = index;
  index = 0;
  if (0 < container[1]) {
    do {
      *(unsigned int *)(*container + index * 0x2c) = 0;
      *(signed char *)(container[2] + index) = -1;
      index = index + 1;
    } while (index < container[1]);
  }
  return;
}
