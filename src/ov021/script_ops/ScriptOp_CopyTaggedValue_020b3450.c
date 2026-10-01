extern unsigned int ResolveTaggedValueRef_020b0374();

unsigned int ScriptOp_CopyTaggedValue_020b3450(void *context,short *operands)

{
  short *source;
  short *destination;
  
  source = ResolveTaggedValueRef_020b0374(context,operands + 4);
  if (*operands == 8) {
    destination = ResolveTaggedValueRef_020b0374(context,operands);
    *destination = *source;
    destination[1] = 0;
    *(unsigned int *)(destination + 2) = *(unsigned int *)(source + 2);
  }
  return 0;
}
