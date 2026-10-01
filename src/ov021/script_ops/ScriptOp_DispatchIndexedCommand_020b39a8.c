#include "nitro/types.h"

typedef void CommandHandler();

extern u32 data_ov021_020b5338;
extern u32 func_ov021_020b0374();

u32 ScriptOp_DispatchIndexedCommand_020b39a8(int context,u32 operands)

{
  int commandOperand;
  
  commandOperand = func_ov021_020b0374(context,operands);
  *(u16 *)(context + 0x2c) = 1;
  *(u32 *)(context + 0x30) = 0;
  if (*(CommandHandler **)((u8 *)&data_ov021_020b5338 + *(int *)(commandOperand + 4) * 4) != (CommandHandler *)0x0) {
    (**(CommandHandler **)((u8 *)&data_ov021_020b5338 + *(int *)(commandOperand + 4) * 4))(context,operands);
  }
  return 0;
}
