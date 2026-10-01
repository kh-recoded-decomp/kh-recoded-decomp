extern unsigned int contextData_020b56a4[];
#define activeObject_020b56ac contextData_020b56a4[2]
extern unsigned int func_ov001_02090fa4();
extern unsigned int func_ov021_020b0374();
extern unsigned int func_ov021_020b03b0();

unsigned int ScriptOp_ApplyTwoObjectValues_020b3534(unsigned int context,int operands)

{
  unsigned int object;
  unsigned int firstValue;
  unsigned int secondValue;
  
  object = activeObject_020b56ac;
  firstValue = func_ov021_020b0374(context,operands);
  secondValue = func_ov021_020b0374(context,operands + 8);
  firstValue = func_ov021_020b03b0(firstValue);
  secondValue = func_ov021_020b03b0(secondValue);
  func_ov001_02090fa4(object,firstValue,secondValue);
  return 0;
}
