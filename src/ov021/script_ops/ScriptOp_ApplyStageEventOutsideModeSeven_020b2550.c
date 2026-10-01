extern unsigned int func_ov001_02063a24();
extern unsigned int func_ov001_02063a38();
extern unsigned int func_ov001_0209cd18();
extern unsigned int func_ov021_020b0374();
extern unsigned int func_ov021_020b03b0();

unsigned int ScriptOp_ApplyStageEventOutsideModeSeven_020b2550(unsigned int context,int operands)

{
  int event;
  unsigned int firstValue;
  unsigned int secondValue;
  unsigned int thirdValue;
  int mode;
  
  event = func_ov021_020b0374(context,operands);
  firstValue = func_ov021_020b0374(context,operands + 8);
  secondValue = func_ov021_020b0374(context,operands + 0x10);
  thirdValue = func_ov021_020b0374(context,operands + 0x18);
  func_ov021_020b03b0(firstValue);
  func_ov021_020b03b0(secondValue);
  func_ov021_020b03b0(thirdValue);
  mode = func_ov001_02063a24();
  if (mode != 0) {
    mode = func_ov001_02063a38();
  }
  else {
    mode = 0;
  }
  if (mode != 7) {
    func_ov001_0209cd18(*(unsigned int *)(event + 4) & 0xffff);
  }
  return 0;
}
