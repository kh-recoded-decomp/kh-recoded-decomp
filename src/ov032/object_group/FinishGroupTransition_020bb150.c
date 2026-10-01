extern int contextData_020c0060[];
#define activeGroup_020c0064 contextData_020c0060[1]
extern unsigned int _data_ov001_020a0460;
extern unsigned int func_ov001_0206a814();
extern unsigned int func_ov001_0207b704();

unsigned int FinishGroupTransition_020bb150(void)

{
  int group;
  int ready;
  
  group = activeGroup_020c0064;
  ready = func_ov001_0206a814();
  if (ready == 0) {
    return 0xffffffff;
  }
  *(unsigned short *)(group + 6) = *(unsigned short *)(group + 6) & 0xffdf;
  if ((*(unsigned short *)(group + 6) & 0x4000) == 0) {
    if (*(char *)(group + 8) != '\x03') {
      *(unsigned int *)(_data_ov001_020a0460 + 0x214) = *(unsigned int *)(_data_ov001_020a0460 + 0x214) & 0xfffbffff
      ;
      func_ov001_0207b704();
    }
    *(signed char *)(group + 8) = -1;
  }
  return 7;
}
