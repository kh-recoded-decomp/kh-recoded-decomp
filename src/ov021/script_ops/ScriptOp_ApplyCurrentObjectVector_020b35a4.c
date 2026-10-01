#include "nitro/types.h"

extern struct { int reserved[2]; u32 object; } scriptState_020b56a4;
#define currentScriptObject scriptState_020b56a4.object
extern u32 func_ov001_02091094();
extern u32 func_ov021_020b0374();
extern u32 func_ov021_020b03b0();
extern u32 func_ov021_020b03c8();

u32
ScriptOp_ApplyCurrentObjectVector_020b35a4(u32 context,int operands,u32 unused,u32 argument)

{
  u32 object;
  u32 firstValue;
  u32 secondValue;
  u8 vector [12];
  u32 savedArgument;
  
  object = currentScriptObject;
  savedArgument = argument;
  firstValue = func_ov021_020b0374(context,operands + 8);
  secondValue = func_ov021_020b0374(context,operands + 0x10);
  func_ov021_020b03c8(context,operands,vector);
  firstValue = func_ov021_020b03b0(firstValue);
  secondValue = func_ov021_020b03b0(secondValue);
  func_ov001_02091094(object,vector,firstValue,secondValue);
  return 0;
}
