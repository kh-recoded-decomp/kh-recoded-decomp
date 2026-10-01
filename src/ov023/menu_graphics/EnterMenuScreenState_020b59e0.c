extern unsigned int _data_ov023_020b6f60;
extern unsigned int func_ov001_0207b180();
extern unsigned int func_ov023_020b5924();
extern unsigned int func_ov023_020b5a2c(void);
extern unsigned int func_ov023_020b5a30();

unsigned int EnterMenuScreenState_020b59e0(void)

{
  unsigned int nextState;
  
  nextState = 0;
  if (*(int *)(_data_ov023_020b6f60 + 4) != 0) {
    nextState = (unsigned int)func_ov023_020b5a2c;
    func_ov023_020b5924(_data_ov023_020b6f60);
    func_ov001_0207b180();
    func_ov023_020b5a30();
  }
  return nextState;
}
