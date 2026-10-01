extern int contextData_020b56a4[];
#define activeObject_020b56ac contextData_020b56a4[2]
extern unsigned int VEC_Mag_01ff9f28();
extern unsigned int func_01ff9c84();
extern unsigned int func_01ff9e3c();
extern unsigned int func_ov001_020910c4();
extern unsigned int func_ov021_020b0374();
extern unsigned int func_ov021_020b03b0();
extern unsigned int func_ov021_020b03c8();

unsigned int ScriptOp_MoveObjectWithSpeed_020b34d4(unsigned int context,int operands)

{
  int object;
  int speed;
  unsigned int duration;
  unsigned char position [12];
  unsigned char delta [12];
  
  speed = func_ov021_020b0374(context,operands + 8);
  object = activeObject_020b56ac;
  speed = func_ov021_020b03b0(speed);
  duration = 0xffffffff;
  func_ov021_020b03c8(context,operands,position);
  if (speed != 0) {
    func_01ff9e3c(position,object + 0x2c0,delta);
    duration = VEC_Mag_01ff9f28(delta);
    duration = func_01ff9c84(duration,speed);
  }
  func_ov001_020910c4(object,position,duration,0);
  return 0;
}
