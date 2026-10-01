extern unsigned int func_0202ef24();

void AdvanceObjectAnimationTracks_020a9aa4(unsigned int *object,unsigned int delta)

{
  short status;
  
  if ((*object & 1) != 0) {
    if (object[0x43] != 0) {
      func_0202ef24(object + 2,delta);
    }
    if (((*object & 0x400) != 0) &&
       (status = func_0202ef24(object[0x8a],delta), (status & 1) != 0)) {
      *object = *object & 0xfffffbff;
    }
  }
  return;
}
