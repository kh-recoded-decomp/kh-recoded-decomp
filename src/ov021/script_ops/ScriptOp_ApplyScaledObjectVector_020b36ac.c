extern unsigned int VEC_MultAdd_01ffa09c();
extern unsigned int func_ov001_020910c4();
extern unsigned int func_ov021_020b02b8();
extern unsigned int func_ov021_020b0374();
extern unsigned int func_ov021_020b03b0();
extern unsigned int func_ov021_020b03c8();

unsigned int
ScriptOp_ApplyScaledObjectVector_020b36ac(unsigned int context,int operands,unsigned int argument,unsigned int savedArgument)

{
  int object;
  unsigned int scale;
  unsigned int firstValue;
  unsigned int secondValue;
  unsigned char inputVector [12];
  unsigned char resultVector [12];
  unsigned int saved;
  
  saved = savedArgument;
  object = func_ov021_020b0374(context,operands);
  scale = func_ov021_020b0374(context,operands + 0x10);
  firstValue = func_ov021_020b0374(context,operands + 0x18);
  secondValue = func_ov021_020b0374(context,operands + 0x20);
  object = func_ov021_020b02b8(context,*(unsigned int *)(object + 4));
  if (object != 0) {
    func_ov021_020b03c8(context,operands + 8,inputVector);
    scale = func_ov021_020b03b0(scale);
    VEC_MultAdd_01ffa09c(scale,inputVector,object + 0x2c0,resultVector);
    scale = func_ov021_020b03b0(firstValue);
    firstValue = func_ov021_020b03b0(secondValue);
    func_ov001_020910c4(object,resultVector,scale,firstValue);
  }
  return 0;
}
