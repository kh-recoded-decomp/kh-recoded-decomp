extern unsigned int func_ov017_020a500c();

unsigned short AppendFieldValueSlot_020a3f84(int object)

{
  unsigned short index;
  
  index = *(unsigned short *)(object + 0x1ea);
  *(unsigned short *)(object + 0x1ea) = index + 1;
  func_ov017_020a500c(*(int *)(object + 0x1d4) + (unsigned int)index * 4);
  return *(unsigned short *)(object + 0x1ea) + -1;
}
