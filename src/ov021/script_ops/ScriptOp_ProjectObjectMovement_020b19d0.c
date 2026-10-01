extern int contextData_020b56a4[];
#define activeObject_020b56ac contextData_020b56a4[2]
extern unsigned int VEC_MultAdd_01ffa09c();
extern unsigned int func_ov021_020afd28();
extern unsigned int func_ov021_020b0374();
extern unsigned int func_ov021_020b03b0();

unsigned int ScriptOp_ProjectObjectMovement_020b19d0(int context,int operands,unsigned int argument,unsigned int savedArgument)

{
  unsigned int scale;
  int object;
  unsigned char normal [12];
  unsigned char correction [12];
  unsigned int saved;
  
  saved = savedArgument;
  scale = func_ov021_020b0374(context,operands + 8);
  object = activeObject_020b56ac;
  scale = func_ov021_020b03b0(scale);
  VEC_MultAdd_01ffa09c(scale,object + 0x38c,object + 0x2c0,context + 0x34);
  object = func_ov021_020afd28(object + 0x2c0,object + 0x38c,normal,correction,0);
  if (object != 0) {
    VEC_MultAdd_01ffa09c(0x19a,normal,context + 0x34,context + 0x34);
  }
  return 0;
}
