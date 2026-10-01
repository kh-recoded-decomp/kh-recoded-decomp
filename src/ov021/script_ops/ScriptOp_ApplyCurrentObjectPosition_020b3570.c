#include "nitro/types.h"

extern struct { int reserved[2]; u32 object; } scriptState_020b56a4;
#define currentScriptObject scriptState_020b56a4.object
extern u32 func_ov001_02090fd8();
extern u32 func_ov021_020b0374();
extern u32 func_ov021_020b03c8();

u32 ScriptOp_ApplyCurrentObjectPosition_020b3570(u32 context,int operands)

{
  u32 object;
  int valueOperand;
  u8 vector [12];
  
  valueOperand = func_ov021_020b0374(context,operands + 8);
  object = currentScriptObject;
  func_ov021_020b03c8(context,operands,vector);
  func_ov001_02090fd8(object,vector,*(u32 *)(valueOperand + 4));
  return 0;
}
