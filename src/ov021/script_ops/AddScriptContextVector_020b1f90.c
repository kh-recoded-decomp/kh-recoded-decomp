#include "nitro/types.h"

extern u32 ResolveTaggedValueRef_020b0374();
extern u32 TaggedValueToFixed_020b03b0();

u32 AddScriptContextVector_020b1f90(void *context,int operands)

{
  void *xOperand;
  void *yOperand;
  void *zOperand;
  int component;
  
  xOperand = ResolveTaggedValueRef_020b0374(context,(void *)(operands + 8));
  yOperand = ResolveTaggedValueRef_020b0374(context,(void *)(operands + 0x10));
  zOperand = ResolveTaggedValueRef_020b0374(context,(void *)(operands + 0x18));
  component = TaggedValueToFixed_020b03b0(xOperand);
  *(int *)((int)context + 0x34) = *(int *)((int)context + 0x34) + component;
  component = TaggedValueToFixed_020b03b0(yOperand);
  *(int *)((int)context + 0x38) = *(int *)((int)context + 0x38) + component;
  component = TaggedValueToFixed_020b03b0(zOperand);
  *(int *)((int)context + 0x3c) = *(int *)((int)context + 0x3c) + component;
  return 0;
}
