extern unsigned int contextData_020b56a4[];
#define activeObject_020b56ac contextData_020b56a4[2]
extern unsigned int func_ov001_0209118c();
extern unsigned int func_ov021_020b0374();
extern unsigned int func_ov021_020b03b0();

unsigned int ScriptOp_SetActiveObjectValue_020b3988(unsigned int context, unsigned int operands)

{
  unsigned int object;
  unsigned int value;
  
  value = func_ov021_020b0374(context,operands);
  object = activeObject_020b56ac;
  value = func_ov021_020b03b0(value);
  func_ov001_0209118c(object,value);
  return 0;
}
